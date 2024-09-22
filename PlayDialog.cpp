#include "PlayDialog.hpp"
#include <QEvent>
#include <iostream>
#include <queue>
#include <QMessageBox>

bool PlayDialog::outOfBound(int x, int y) const
{
    return x < 0 || y < 0 || x >= setting.map_width || y >= setting.map_height;
}

void PlayDialog::applySetting(const DifficultySetting &setting)
{
    this->setFixedSize(setting.map_width * 40, 150 + setting.map_height * 40);
    this->setting = setting;
    this->time_used = 0;
    this->safe_block_remaining = setting.map_width * setting.map_height - setting.cnt_mine;

    grid = Grid(setting.map_width * 40, setting.map_height * 40, setting.map_width, setting.map_height);
    lbl_time.move(20, 80);
    lbl_time.setText("0.00");
    lbl_time.adjustSize();
    timer.stop();

    for (auto _ : grid_btn_mine) {
        for (auto btn : _) {
            delete btn;
        }
    }
    grid_btn_mine.clear();
    grid_btn_mine.resize(setting.map_width);
    for (auto &column : grid_btn_mine) column.resize(setting.map_height);

    for (auto _ : grid_lbl) {
        for (auto lbl : _) {
            delete lbl;
        }
    }
    grid_lbl.clear();
    grid_lbl.resize(setting.map_width);
    for (auto &column : grid_lbl) column.resize(setting.map_height);

    grid_info.resize(setting.map_width);
    for (auto &column : grid_info) column.resize(setting.map_height);

    is_first_click = true;

    for (int i = 0; i < setting.map_width; ++i) {
        for (int j = 0; j < setting.map_height; ++j) {
            QPushButton *btn = new QPushButton(this);
            btn->installEventFilter(this);
            btn->setGeometry(i * 40, 150 + j * 40, 40, 40);
            btn->show();
            grid_btn_mine[i][j] = btn;

            QLabel *lbl = new QLabel(this);
            lbl->move(i * 40, 150 + j * 40);
            grid_lbl[i][j] = lbl;

            grid_info[i][j].is_clear = false;
            grid_info[i][j].is_mine = false;
            grid_info[i][j].cnt_mines_around = 0;
        }
    }
}

void PlayDialog::generateMines(int cl_x, int cl_y)
{
    srand(time(0));

    for (int i = 0; i < setting.cnt_mine; ++i) {
        int p = rand() % (setting.map_width * setting.map_height - i);
        for (int j = 0; j < setting.map_width; ++j) {
            for (int k = 0; k < setting.map_height; ++k) {
                if (grid_info[j][k].is_mine) continue;
                if (j == cl_x && k == cl_y) continue;
                if (p == 0) {
                    grid_info[j][k].is_mine = true;
                }
                --p;
            }
        }
    }

    for (int i = 0; i < setting.map_width; ++i) {
        for (int j = 0; j < setting.map_height; ++j) {
            if (!grid_info[i][j].is_mine) {
                for (int k = 0; k < 8; ++k) {
                    int di = i + DirectionOffset[k][0], dj = j + DirectionOffset[k][1];
                    if (!outOfBound(di, dj) && grid_info[di][dj].is_mine) {
                        ++grid_info[i][j].cnt_mines_around;
                    }
                }
            }
        }
    }

    for (int i = 0; i < setting.map_width; ++i) {
        for (int j = 0; j < setting.map_height; ++j) {
            if (grid_info[i][j].is_mine) {
                putchar('*');
            } else {
                putchar('0' + grid_info[i][j].cnt_mines_around);
            }
        }
        putchar('\n');
    }
}

void PlayDialog::showUp(int x, int y)
{
    assert(!grid_info[x][y].is_mine);
    grid_info[x][y].is_clear = true;
    grid_btn_mine[x][y]->hide();
    if (grid_info[x][y].cnt_mines_around > 0) {
        grid_lbl[x][y]->setText(DigitString[grid_info[x][y].cnt_mines_around]);
        grid_lbl[x][y]->adjustSize();
        grid_lbl[x][y]->show();
    }
}

void PlayDialog::clearAreaAround(int cl_x, int cl_y)
{
    showUp(cl_x, cl_y);
    std::queue<std::pair<int, int>> que;
    que.push({cl_x, cl_y});
    while (!que.empty()) {
        auto pair = que.front();
        que.pop();
        int x = pair.first, y = pair.second;
        --this->safe_block_remaining;
        if (grid_info[x][y].cnt_mines_around > 0) continue;
        for (int d = 0; d < 8; ++d) {
            int dx = x + DirectionOffset[d][0],
                dy = y + DirectionOffset[d][1];
            if (!outOfBound(dx, dy) && !grid_info[dx][dy].is_mine && !grid_info[dx][dy].is_clear) {
                que.push({dx, dy});
                showUp(dx, dy);
            }
        }
    }
}

PlayDialog::PlayDialog(int w, int h) : timer(this), grid(w, h, 1, 1), lbl_time(this)
{
    this->setFixedSize(w, h);
    lbl_time.show();
    connect(&timer, &QTimer::timeout, this, [this](){
        ++time_used;
        char buf[10];
        snprintf(buf, 10, "%d.%d%d", time_used / 100, (time_used / 10) % 10, time_used % 10);
        lbl_time.setText(buf);
        lbl_time.adjustSize();
    });
}

PlayDialog::~PlayDialog()
{
    for (auto _ : grid_btn_mine) {
        for (auto btn : _) {
            delete btn;
        }
    }
    grid_btn_mine.clear();

    for (auto _ : grid_lbl) {
        for (auto lbl : _) {
            delete lbl;
        }
    }
    grid_lbl.clear();
}

bool PlayDialog::eventFilter(QObject *target, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonRelease) {
        bool click_btn = false;
        int cl_x, cl_y;
        for (int i = 0; i < setting.map_width; ++i) {
            for (int j = 0; j < setting.map_height; ++j) {
                if (grid_btn_mine[i][j] == target) {
                    click_btn = true;
                    cl_x = i, cl_y = j;
                    break;
                }
            }
            if (click_btn) break;
        }
        if (click_btn) {
            if (is_first_click) {
                generateMines(cl_x, cl_y);
                assert(!grid_info[cl_x][cl_y].is_mine);
                timer.start(10);
                is_first_click = false;
            }
            if (!grid_info[cl_x][cl_y].is_mine) {
                clearAreaAround(cl_x, cl_y);
                if (safe_block_remaining == 0) {
                    timer.stop();
                    QMessageBox::information(this, "You win", "You have found all the mines!");
                    accept();
                }
            } else {
                QMessageBox::information(this, "You lose", "You hit a mine!");
                accept();
            }
        }
    }
    return QDialog::eventFilter(target, event);
}
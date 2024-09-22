#include "PlayDialog.hpp"
#include <QEvent>
#include <iostream>

bool PlayDialog::outOfBound(int x, int y) const
{
    return x < 0 || y < 0 || x >= setting.map_width || y >= setting.map_height;
}

void PlayDialog::applySetting(const DifficultySetting &setting)
{
    this->setFixedSize(setting.map_width * 40, 150 + setting.map_height * 40);
    this->setting = setting;
    grid = Grid(setting.map_width * 40, setting.map_height * 40, setting.map_width, setting.map_height);
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

PlayDialog::PlayDialog(int w, int h) : grid(w, h, 1, 1)
{
    this->setFixedSize(w, h);
}

PlayDialog::~PlayDialog()
{
    for (auto _ : grid_btn_mine) {
        for (auto btn : _) {
            delete btn;
        }
    }
    grid_btn_mine.clear();
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
                is_first_click = false;
            }
        }
    }
    return QDialog::eventFilter(target, event);
}
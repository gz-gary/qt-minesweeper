#include "PlayDialog.hpp"

void PlayDialog::applySetting(const DifficultySetting &setting)
{
    this->setFixedSize(setting.map_width * 40, 150 + setting.map_height * 40);
    grid = Grid(setting.map_width * 40, setting.map_height * 40, setting.map_width, setting.map_height);
    for (auto _ : grid_btn_mine) {
        for (auto btn : _) {
            delete btn;
        }
    }
    grid_btn_mine.clear();
    grid_btn_mine.resize(setting.map_width);
    for (auto &column : grid_btn_mine) column.resize(setting.map_height);
    for (int i = 0; i < setting.map_width; ++i) {
        for (int j = 0; j < setting.map_height; ++j) {
            QPushButton *btn = new QPushButton(this);
            btn->setGeometry(i * 40, 150 + j * 40, 40, 40);
            btn->show();
            grid_btn_mine[i][j] = btn;
        }
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
    return QDialog::eventFilter(target, event);
}

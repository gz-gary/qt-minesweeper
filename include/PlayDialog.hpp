#pragma once
#include "Grid.hpp"
#include "DifficultyDialog.hpp"
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <vector>

const int DirectionOffset[8][2] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1},
    {1, 1},
    {1, -1},
    {-1, 1},
    {-1, -1},
};

const QString DigitString[10] = {
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
};

class PlayDialog : public QDialog {
private:
    struct GridInfo {
        bool is_mine;
        bool is_clear;
        int cnt_mines_around;
    };

    int safe_block_remaining;
    QTimer timer;
    Grid grid;
    QLabel lbl_time;
    int time_used;
    DifficultySetting setting;
    bool is_first_click;

    std::vector<std::vector<QPushButton*>> grid_btn_mine;
    std::vector<std::vector<QLabel*>> grid_lbl;
    std::vector<std::vector<GridInfo>> grid_info;

    bool outOfBound(int x, int y) const;
    void generateMines(int cl_x, int cl_y);
    void showUp(int x, int y);
    void clearAreaAround(int cl_x, int cl_y);

public:

    void applySetting(const DifficultySetting& setting);

    PlayDialog(int w, int h);
    ~PlayDialog();
    bool eventFilter(QObject *target, QEvent *event);
};
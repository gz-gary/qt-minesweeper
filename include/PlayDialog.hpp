#pragma once
#include "Grid.hpp"
#include "DifficultyDialog.hpp"
#include <QDialog>
#include <QPushButton>
#include <QLabel>
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

class PlayDialog : public QDialog {
private:
    struct GridInfo {
        bool is_mine;
        bool is_clear;
        int cnt_mines_around;
    };
    bool outOfBound(int x, int y) const;
    void generateMines(int cl_x, int cl_y);

public:

    Grid grid;
    DifficultySetting setting;
    std::vector<std::vector<QPushButton*>> grid_btn_mine;
    std::vector<std::vector<QLabel*>> grid_lbl;
    std::vector<std::vector<GridInfo>> grid_info;
    bool is_first_click;

    void applySetting(const DifficultySetting& setting);

    PlayDialog(int w, int h);
    ~PlayDialog();
    bool eventFilter(QObject *target, QEvent *event);
};
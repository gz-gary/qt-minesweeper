#pragma once
#include "Grid.hpp"
#include "DifficultyDialog.hpp"
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <vector>

class PlayDialog : public QDialog {
private:

public:

    Grid grid;
    std::vector<std::vector<QPushButton*>> grid_btn_mine;

    void applySetting(const DifficultySetting& setting);

    PlayDialog(int w, int h);
    ~PlayDialog();
    bool eventFilter(QObject *target, QEvent *event);
};

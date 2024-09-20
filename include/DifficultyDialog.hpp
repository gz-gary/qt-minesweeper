#pragma once
#include "Grid.hpp"
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QValidator>

struct DifficultySetting {
    int map_width;
    int map_height;
    int cnt_mine;
};

class DifficultyDialog : public QDialog {
private:

    enum Difficulty{
        Easy,
        Moderate,
        Hard,
        Custom
    } difficulty_selected;

public:

    Grid grid;
    QPushButton btn_easy_mode,
                btn_moderate_mode,
                btn_hard_mode,
                btn_custom_mode;
    QLineEdit   lned_map_width,
                lned_map_height,
                lned_cnt_mine;
    QLabel      lbl_map_width,
                lbl_map_height,
                lbl_cnt_mine;
    QIntValidator  vld_map_size,
                   vld_cnt_mine;

    DifficultyDialog(int w, int h);
    ~DifficultyDialog();
    bool eventFilter(QObject *target, QEvent *event);

    // std::optional<DifficultySetting> selected_difficulty;
    DifficultySetting extractSetting() const;
};

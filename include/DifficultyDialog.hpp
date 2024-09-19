#pragma once
#include "Grid.hpp"
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <optional>

struct DifficultySetting {
    int map_width;
    int map_height;
    int cnt_mine;
};

class DifficultyDialog : public QDialog {
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

    DifficultyDialog(int w, int h);
    ~DifficultyDialog();
    bool eventFilter(QObject *target, QEvent *event);

    // std::optional<DifficultySetting> selected_difficulty;
    std::optional<DifficultySetting> extractSetting() const;
};

#include "DifficultyDialog.hpp"
#include <set>
#include <QEvent>
#include <iostream>
#include <QMessageBox>

DifficultyDialog::DifficultyDialog(int w, int h) :
    grid(w, h, 4, 8),
    btn_easy_mode(this),
    btn_moderate_mode(this),
    btn_hard_mode(this),
    btn_custom_mode(this),
    lned_map_width(this),
    lned_map_height(this),
    lned_cnt_mine(this),
    lbl_map_width(this),
    lbl_map_height(this),
    lbl_cnt_mine(this)
{
    btn_easy_mode.setGeometry(grid.fwi(0), grid.fhi(0), grid.fwi(4), grid.fhi(2));
    btn_easy_mode.installEventFilter(this);
    btn_easy_mode.setText("Easy Mode");
    btn_easy_mode.show();

    btn_moderate_mode.setGeometry(grid.fwi(0), grid.fhi(2), grid.fwi(4), grid.fhi(2));
    btn_moderate_mode.installEventFilter(this);
    btn_moderate_mode.setText("Moderate Mode");
    btn_moderate_mode.show();

    btn_hard_mode.setGeometry(grid.fwi(0), grid.fhi(4), grid.fwi(4), grid.fhi(2));
    btn_hard_mode.installEventFilter(this);
    btn_hard_mode.setText("Hard Mode");
    btn_hard_mode.show();

    btn_custom_mode.setGeometry(grid.fwi(2), grid.fhi(6), grid.fwi(2), grid.fhi(2));
    btn_custom_mode.installEventFilter(this);
    btn_custom_mode.setText("Custom Mode");
    btn_custom_mode.show();

    lned_map_width.setGeometry(grid.fwd(0.27), grid.fhd(0.78), grid.fwd(0.2), grid.fhd(0.05));
    connect(
        &lned_map_width,
        &QLineEdit::textChanged,
        this,
        [this](const QString &text) {
            QString copy = text;
            int len = text.length();
            bool flag = false;
            int value = copy.toInt(&flag);
            if (!flag || (value > 50)) {
                lned_map_width.setText(copy.left(len - 1));
            }
        }
    );
    lned_map_width.installEventFilter(this);
    lned_map_width.show();

    lned_map_height.setGeometry(grid.fwd(0.27), grid.fhd(0.78 + 0.07), grid.fwd(0.2), grid.fhd(0.05));
    connect(
        &lned_map_height,
        &QLineEdit::textChanged,
        this,
        [this](const QString &text) {
            QString copy = text;
            int len = text.length();
            bool flag = false;
            int value = copy.toInt(&flag);
            if (!flag || (value > 50)) {
                lned_map_height.setText(copy.left(len - 1));
            }
        }
    );
    lned_map_height.installEventFilter(this);
    lned_map_height.show();

    lned_cnt_mine.setGeometry(grid.fwd(0.27), grid.fhd(0.78 + 0.07 + 0.07), grid.fwd(0.2), grid.fhd(0.05));
    connect(
        &lned_cnt_mine,
        &QLineEdit::textChanged,
        this,
        [this](const QString &text) {
            QString copy = text;
            int len = text.length();
            bool flag = false;
            int value = copy.toInt(&flag);
            if (!flag || (value > 1200)) {
                lned_cnt_mine.setText(copy.left(len - 1));
            }
        }
    );
    lned_cnt_mine.installEventFilter(this);
    lned_cnt_mine.show();

    lbl_map_width.setGeometry(grid.fwd(0.02), grid.fhd(0.78), grid.fwd(0.2), grid.fhd(0.05));
    lbl_map_width.setText("Map Width");
    lbl_map_width.adjustSize();
    lbl_map_width.installEventFilter(this);
    lbl_map_width.show();

    lbl_map_height.setGeometry(grid.fwd(0.02), grid.fhd(0.78 + 0.07), grid.fwd(0.2), grid.fhd(0.05));
    lbl_map_height.setText("Map Height");
    lbl_map_height.adjustSize();
    lbl_map_height.installEventFilter(this);
    lbl_map_height.show();

    lbl_cnt_mine.setGeometry(grid.fwd(0.02), grid.fhd(0.78 + 0.07 + 0.07), grid.fwd(0.2), grid.fhd(0.05));
    lbl_cnt_mine.setText("Count of Mines");
    lbl_cnt_mine.adjustSize();
    lbl_cnt_mine.installEventFilter(this);
    lbl_cnt_mine.show();

    this->setFixedSize(w, h);
}

DifficultyDialog::~DifficultyDialog()
{
}

bool DifficultyDialog::eventFilter(QObject *target, QEvent *event)
{
    if (
        event->type() == QEvent::MouseButtonRelease
        && std::set<QObject*>(
            {
                &btn_easy_mode,
                &btn_moderate_mode,
                &btn_hard_mode,
                &btn_custom_mode
            }
        ).count(target) >= 1
    ) {
        if (target == &btn_easy_mode) {
            difficulty_selected = Difficulty::Easy;
            accept();
        } else if (target == &btn_moderate_mode) {
            difficulty_selected = Difficulty::Moderate;
            accept();
        } else if (target == &btn_hard_mode) {
            difficulty_selected = Difficulty::Hard;
            accept();
        } else {
            QString text_map_width = lned_map_width.text(),
                    text_map_height = lned_map_height.text(),
                    text_cnt_mine = lned_cnt_mine.text();
            bool flag = false, tag = true;
            int value_map_width = text_map_width.toInt(&flag);
            if (!flag || value_map_width < 9 || value_map_width > 50) tag = false;
            int value_map_height = text_map_height.toInt(&flag);
            if (!flag || value_map_height < 9 || value_map_height > 50) tag = false;
            int value_cnt_mine = text_cnt_mine.toInt(&flag);
            if (!flag || (tag && (value_cnt_mine < 1 || value_cnt_mine >= value_map_height * value_map_width))) tag = false;
            if (!tag) {
                QMessageBox::warning(this, "Invalid custom settings!", R"(Custom settings must follow these rules:
1. Width and height of map must be in [9, 50]
2. Count of mines must be in [1, Size of map - 1])");
                lned_map_width.setText("9");
                lned_map_height.setText("9");
                lned_cnt_mine.setText("10");
            } else {
                difficulty_selected = Difficulty::Custom;
                accept();
            }
        }
    }

    return QDialog::eventFilter(target, event);
}

DifficultySetting DifficultyDialog::extractSetting() const
{
    DifficultySetting result;
    bool flag;

    switch (difficulty_selected) {
    case Difficulty::Easy:
        result.map_width = 9;
        result.map_height = 9;
        result.cnt_mine = 10;
        break;
    case Difficulty::Moderate:
        result.map_width = 16;
        result.map_height = 16;
        result.cnt_mine = 40;
        break;
    case Difficulty::Hard:
        result.map_width = 30;
        result.map_height = 16;
        result.cnt_mine = 99;
        break;
    case Difficulty::Custom:
        result.map_width = lned_map_width.text().toInt(&flag);
        result.map_height = lned_map_height.text().toInt(&flag);
        result.cnt_mine = lned_cnt_mine.text().toInt(&flag);
        break;
    }

    return result;
}

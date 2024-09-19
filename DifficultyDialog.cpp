#include "DifficultyDialog.hpp"
#include <set>
#include <QEvent>

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
    lned_map_width.installEventFilter(this);
    lned_map_width.show();

    lned_map_height.setGeometry(grid.fwd(0.27), grid.fhd(0.78 + 0.07), grid.fwd(0.2), grid.fhd(0.05));
    lned_map_height.installEventFilter(this);
    lned_map_height.show();

    lned_cnt_mine.setGeometry(grid.fwd(0.27), grid.fhd(0.78 + 0.07 + 0.07), grid.fwd(0.2), grid.fhd(0.05));
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
                &btn_custom_mode,
                &btn_easy_mode,
                &btn_moderate_mode,
                &btn_hard_mode
            }
        ).count(target) >= 1
    ) {
        accept();
    }
    return QDialog::eventFilter(target, event);
}

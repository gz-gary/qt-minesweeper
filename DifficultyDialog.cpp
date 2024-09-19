#include "DifficultyDialog.hpp"
#include <set>
#include <QEvent>

DifficultyDialog::DifficultyDialog(int w, int h) :
    grid(w, h, 4, 8),
    btn_easy_mode(this),
    btn_moderate_mode(this),
    btn_hard_mode(this),
    btn_custom_mode(this),
    ledt_map_width(this)
{
    btn_easy_mode.setGeometry(grid.fwi(0), grid.fhi(0), grid.fwi(4), grid.fhi(2));
    btn_easy_mode.installEventFilter(this);
    btn_easy_mode.show();

    btn_moderate_mode.setGeometry(grid.fwi(0), grid.fhi(2), grid.fwi(4), grid.fhi(2));
    btn_moderate_mode.installEventFilter(this);
    btn_moderate_mode.show();

    btn_hard_mode.setGeometry(grid.fwi(0), grid.fhi(4), grid.fwi(4), grid.fhi(2));
    btn_hard_mode.installEventFilter(this);
    btn_hard_mode.show();

    btn_custom_mode.setGeometry(grid.fwi(2), grid.fhi(6), grid.fwi(2), grid.fhi(2));
    btn_custom_mode.installEventFilter(this);
    btn_custom_mode.show();

    ledt_map_width.setGeometry(grid.fwd(0.05), grid.fhd(0.8), grid.fwd(0.2), grid.fhd(0.05));
    ledt_map_width.installEventFilter(this);
    ledt_map_width.show();
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

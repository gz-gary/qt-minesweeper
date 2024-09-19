#include "Grid.hpp"
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>

class DifficultyDialog : public QDialog {
public:
    Grid grid;
    QPushButton btn_easy_mode,
                btn_moderate_mode,
                btn_hard_mode,
                btn_custom_mode;
    QLineEdit ledt_map_width,
              ledt_map_height,
              ledt_cnt_mine;

    DifficultyDialog(int w, int h);
    ~DifficultyDialog();
    bool eventFilter(QObject *target, QEvent *event);
};

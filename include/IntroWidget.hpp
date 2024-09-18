#pragma once
#include <functional>
#include <QWidget>
#include <QPushButton>

class IntroWidget : public QWidget {
public:
    QPushButton btn_start_game,
                btn_settings,
                btn_exit;
    const std::function<int(int)> fw, fh;

    const static int GRID_CNT_W = 5,
                     GRID_CNT_H = 5;
    
    IntroWidget(int w, int h);
    ~IntroWidget();
};
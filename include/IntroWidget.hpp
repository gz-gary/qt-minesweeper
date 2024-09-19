#pragma once
#include "Grid.hpp"
#include <functional>
#include <QWidget>
#include <QPushButton>

class IntroWidget : public QWidget {
public:
    QPushButton btn_start_game,
                btn_settings,
                btn_exit;
    Grid grid;
    
    IntroWidget(int w, int h);
    ~IntroWidget();
};
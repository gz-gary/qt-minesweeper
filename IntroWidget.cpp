#include "IntroWidget.hpp"
#include <functional>
#include <QWidget>
#include <QPushButton>
#include <QEvent>
#include <iostream>

IntroWidget::IntroWidget(int w, int h) : 
    btn_start_game(this),
    btn_settings(this),
    btn_exit(this),
    grid(w, h, 5, 5)
{
    btn_start_game.setGeometry(grid.fwi(1), grid.fhi(1), grid.fwi(3), grid.fhi(1));
    btn_start_game.setText("Start game");
    btn_start_game.installEventFilter(this);
    btn_start_game.show();
    btn_settings.setGeometry(grid.fwi(1), grid.fhi(2), grid.fwi(3), grid.fhi(1));
    btn_settings.setText("Settings");
    btn_settings.show();
    btn_exit.setGeometry(grid.fwi(1), grid.fhi(3), grid.fwi(3), grid.fhi(1));
    btn_exit.setText("Exit");
    btn_exit.show();

    this->setFixedSize(w, h);
}

IntroWidget::~IntroWidget()
{
}

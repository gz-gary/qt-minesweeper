#include "IntroWidget.hpp"
#include <functional>
#include <QWidget>
#include <QPushButton>
#include <QEvent>
#include <iostream>

IntroWidget::IntroWidget(int w, int h) : 
    QWidget(nullptr),
    btn_start_game(this),
    btn_settings(this),
    btn_exit(this),
    fw([w](int w0) { return std::floor(1.0 * w0 / GRID_CNT_W * w); }),
    fh([h](int h0) { return std::floor(1.0 * h0 / GRID_CNT_H * h); })
{
    this->resize(w, h);
    btn_start_game.resize(fw(3), fh(1));
    btn_start_game.move(fw(1), fh(1));
    btn_start_game.setText("Start game");
    btn_start_game.installEventFilter(this);
    btn_start_game.show();
    btn_settings.resize(fw(3), fh(1));
    btn_settings.move(fw(1), fh(2));
    btn_settings.setText("Settings");
    btn_settings.show();
    btn_exit.resize(fw(3), fh(1));
    btn_exit.move(fw(1), fh(3));
    btn_exit.setText("Exit");
    btn_exit.show();
}

IntroWidget::~IntroWidget()
{
}

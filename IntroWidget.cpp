#include "IntroWidget.hpp"
#include <functional>
#include <QWidget>
#include <QPushButton>

IntroWidget::IntroWidget(int w, int h)  : 
    btn_start_game(this),
    btn_settings(this),
    btn_exit(this),
    fw([w](double ratio) { return std::floor(ratio * w); }),
    fh([h](double ratio) { return std::floor(ratio * h); })
{
    this->resize(w, h);
    btn_start_game.resize(fw(0.35), fh(0.10));
    btn_start_game.move(fw(0.5-0.35/2), fh(0.10));
    btn_start_game.show();
    btn_settings.resize(fw(0.35), fh(0.10));
    btn_settings.move(fw(0.5-0.35/2), fh(0.20));
    btn_settings.show();
    btn_exit.resize(fw(0.35), fh(0.10));
    btn_exit.move(fw(0.5-0.35/2), fh(0.30));
    btn_exit.show();
    this->show();
}
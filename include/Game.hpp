#pragma once
#include "IntroWidget.hpp"
#include <QWidget>
#include <QDialog>

class Game : public QObject {
public:
    IntroWidget intro_widget;
    QDialog dialog_widget;

    Game();
    ~Game();
    bool eventFilter(QObject *target, QEvent *event);
};
#pragma once
#include "IntroWidget.hpp"
#include "DifficultyDialog.hpp"
#include "PlayDialog.hpp"
#include <QWidget>
#include <QDialog>

class Game : public QObject {
public:
    IntroWidget intro_widget;
    DifficultyDialog difficulty_dialog;
    PlayDialog play_dialog;

    Game();
    ~Game();
    bool eventFilter(QObject *target, QEvent *event);
};
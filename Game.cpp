#include "Game.hpp"
#include <QDialog>
#include <QEvent>
#include <iostream>

Game::Game() :
    intro_widget(500, 500),
    difficulty_dialog(400, 360)
{
    intro_widget.btn_start_game.installEventFilter(this);
    intro_widget.btn_exit.installEventFilter(this);
    intro_widget.show();
}

Game::~Game()
{
}

bool Game::eventFilter(QObject * target, QEvent * event) {
    
    if (
        event->type() == QEvent::MouseButtonRelease
        && target == &intro_widget.btn_start_game
    ) {
        int value = difficulty_dialog.exec();
        std::cout << "Dialog returns " << value << std::endl;
    }

    if (
        event->type() == QEvent::MouseButtonRelease
        && target == &intro_widget.btn_exit
    ) {
        std::cout << "Exit game" << std::endl;
        exit(0);
    }
    return QObject::eventFilter(target, event);
}
#include "Game.hpp"
#include <QDialog>
#include <QEvent>
#include <iostream>

Game::Game() :
    intro_widget(500, 500),
    dialog_widget()
{
    intro_widget.btn_start_game.installEventFilter(this);
    intro_widget.show();

    dialog_widget.resize(300, 300);
}

Game::~Game()
{
}

bool Game::eventFilter(QObject * target, QEvent * event) {
    
    if (target == &intro_widget.btn_start_game && event->type() == QEvent::MouseButtonPress) {
        std::cout << "Start Game Clicked Detected" << std::endl;
        dialog_widget.exec();
        return true;
    }
    return QObject::eventFilter(target, event);
}
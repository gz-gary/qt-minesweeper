#include "Game.hpp"
#include <QDialog>
#include <QEvent>
#include <QSizePolicy>
#include <iostream>

Game::Game() :
    intro_widget(500, 500),
    difficulty_dialog(400, 360),
    play_dialog(1000, 1000)
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
        if (value == QDialog::Accepted) {
            DifficultySetting setting = difficulty_dialog.extractSetting();
            /*
            std::cout << "Map Width: " << setting.map_width << std::endl;
            std::cout << "Map Height: " << setting.map_height << std::endl;
            std::cout << "Count of Mines: " << setting.cnt_mine << std::endl;
            */

            intro_widget.hide();
            play_dialog.applySetting(setting);
            play_dialog.exec();
            intro_widget.show();
        }
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
#include "Game.hpp"
#include <QDialog>
#include <QEvent>
#include <QSizePolicy>
#include <iostream>

Game::Game() :
    intro_widget(500, 500),
    difficulty_dialog(400, 360)
{
    intro_widget.setFixedSize(intro_widget.size());
    difficulty_dialog.setFixedSize(difficulty_dialog.size());
    intro_widget.show();

    intro_widget.btn_start_game.installEventFilter(this);
    intro_widget.btn_exit.installEventFilter(this);
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
        if (value == QDialog::Accepted) {
            std::optional<DifficultySetting> setting = difficulty_dialog.extractSetting();
            if (setting.has_value()) {
                std::cout << "Map Width: " << setting->map_width << std::endl;
                std::cout << "Map Height: " << setting->map_height << std::endl;
                std::cout << "Count of Mines: " << setting->cnt_mine << std::endl;
            } else {
                std::cout << "Format wrong!" << std::endl;
            }
            /*
            intro_widget.hide();
            intro_widget.show();
            */
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
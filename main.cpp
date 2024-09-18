#include "Game.hpp"
#include <iostream>
#include <QWidget>
#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication app{argc, argv};
	Game game;
	std::cout << "Hello, world!" << std::endl;
	return app.exec();
}

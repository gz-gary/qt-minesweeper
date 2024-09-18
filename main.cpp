#include "IntroWidget.hpp"
#include <iostream>
#include <QWidget>
#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication app{argc, argv};
	IntroWidget w{300, 300};
	std::cout << "Hello, world!" << std::endl;
	return app.exec();
}

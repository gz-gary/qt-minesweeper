#include <iostream>
#include <QWidget>
#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication app{argc, argv};
	QWidget w;
	w.resize(300, 300);
	w.show();
	std::cout << "Hello, world!" << std::endl;
	return app.exec();
}

#include <functional>
#include <QWidget>
#include <QPushButton>

class IntroWidget : public QWidget {
private:
    QPushButton btn_start_game,
                btn_settings,
                btn_exit;
    const std::function<int(double)> fw, fh;

public:
    IntroWidget(int w, int h);
};
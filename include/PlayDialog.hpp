#pragma once
#include "Grid.hpp"
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class PlayDialog : public QDialog {
public:
    Grid grid;

    PlayDialog(int w, int h);
    ~PlayDialog();
    bool eventFilter(QObject *target, QEvent *event);
};
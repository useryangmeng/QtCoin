#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtCoin.h"

class QtCoin : public QMainWindow
{
    Q_OBJECT

public:
    QtCoin(QWidget *parent = nullptr);
    ~QtCoin();
    void paintEvent(QPaintEvent*);
private:
    Ui::QtCoinClass ui;
};

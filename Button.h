#pragma once

#include <QMainWindow>
#include "ui_Button.h"

class Button : public QMainWindow
{
	Q_OBJECT

public:
	Button(QWidget *parent = nullptr);
	~Button();

private:
	Ui::ButtonClass ui;
};

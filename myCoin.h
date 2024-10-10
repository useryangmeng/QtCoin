#pragma once

#include <QPushButton>

class myCoin  : public QPushButton
{
	Q_OBJECT

public:
	myCoin(QWidget *parent);
	myCoin(QString butImg);
	~myCoin();

	void changeFlag();
	QTimer* timer1; //正面翻反面 定时器
	QTimer* timer2; //反面翻正面 定时器
	int min = 1; //最小图片
	int max = 8; //最大图片
	int posX; //x坐标
	int posY; //y坐标
	bool flag;
	
private:

signals:
};

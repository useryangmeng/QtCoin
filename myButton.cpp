#include "myButton.h"
#include <QPushButton>
#include <QPixmap>

myButton::myButton(QWidget* parent) :QPushButton(parent)
{

}

myButton::myButton(QString normalImg, QString pressedImg)
{
	normalImgPath = normalImg;
	PressedImgPath = pressedImg;

	QPixmap pix;
	bool ret = pix.load(normalImgPath);
	if (!ret)
	{
		qDebug() << "start button load fail";
	}
	qDebug() << "start button load succeed";
	this->setFixedSize(pix.width(), pix.height());
	this->setStyleSheet("QPushButton{border:0px}");
	this->setIcon(pix);
	this->setIconSize(QSize(pix.width(), pix.height()));
}

void myButton::mousePressEvent(QMouseEvent* ev)
{
	if (PressedImgPath != "")
	{
		QPixmap pix;
		int ret = pix.load(PressedImgPath);
		if (!ret)
		{
			qDebug() << "pressedimg load false mybuttoncpp";
		}
		this->setFixedSize(pix.size());
		this->setStyleSheet("QPushButton{border:0px;}");
		this->setIcon(pix);
		this->setIconSize(pix.size());
	}
	return QPushButton::mousePressEvent(ev);
}

void myButton::mouseReleaseEvent(QMouseEvent* ev)
{
	if (normalImgPath != "") //选中路径不为空，显示选中图片
	{
		QPixmap pixmap;
		bool ret = pixmap.load(normalImgPath);
		if (!ret)
		{
			qDebug() << normalImgPath << "加载图片失败!";
		}
		this->setFixedSize(pixmap.width(), pixmap.height());
		this->setStyleSheet("QPushButton{border:0px;}");
		this->setIcon(pixmap);
		this->setIconSize(QSize(pixmap.width(), pixmap.height()));
	}
	//交给父类执行 释放事件
	return QPushButton::mouseReleaseEvent(ev);
}
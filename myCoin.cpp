#include "myCoin.h"
#include <QTimer>

myCoin::myCoin(QWidget *parent)
	: QPushButton(parent)
{}

myCoin::myCoin(QString butImg)
{
    //初始化定时器
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    QPixmap pixmap;
    bool ret = pixmap.load(butImg);
    if (!ret)
    {
        qDebug() << butImg << "加载图片失败!";
    }

    this->setFixedSize(pixmap.width(), pixmap.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(), pixmap.height()));

    //监听正面翻转的信号槽
    connect(timer1, &QTimer::timeout, [=]() {
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
        if (this->min > this->max) //如果大于最大值，重置最小值，并停止定时器
        {
            this->min = 1;
            timer1->stop();
        }
    });

    connect(timer2, &QTimer::timeout, [=]() {
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1.png").arg((this->max)--);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
        if (this->max < this->min) //如果小于最小值，重置最大值，并停止定时器
        {
            this->max = 8;
            timer2->stop();
        }
    });
}

void myCoin::changeFlag()
{
    if (this->flag)
    {
        timer1->start(30);
        this->flag = false;
    }
    else
    {
        timer2->start(30);
        this->flag = true;
    }
}

myCoin::~myCoin()
{}

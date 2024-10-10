#include "QtCoin.h"
#include <QPixmap>
#include <QDebug>
#include <QPainter>
#include <QPushButton>
#include <QSize>
#include <QTImer>

#include <QMediaPlayer>

#include "myButton.h"
#include "ChooseLevelScene.h"


QtCoin::QtCoin(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
   

    QMediaPlayer* winplayer = new QMediaPlayer(this);
    // 设置音频文件来源
    winplayer->setSource(QUrl::fromLocalFile(":/res/LevelWinSound.wav"));
    // 播放音频
    winplayer->play();

    this->setFixedSize(320, 588);//设置固定大小
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));//窗口标题图片
    qDebug() << "main window title pic set";
    this->setWindowTitle("翻金币");

    connect(this->ui.actionQuit,&QAction::triggered,this,&QWidget::close);//点击退出

    myButton* startBtn = new myButton(":/res/MenuSceneStartButton.png", "");//start 按钮
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.7);

    ChooseLevelScene* chooseScene = new ChooseLevelScene;//new window

    int newWidth = static_cast<int>(startBtn->iconSize().width() *0.5);
    int newHeight = static_cast<int>(startBtn->iconSize().height() *0.5);
    startBtn->setIconSize(QSize(newWidth, newHeight));

    qDebug() << "start button size" << startBtn->width();
    qDebug() << "start icon size" << startBtn->iconSize().width();

    connect(startBtn, &myButton::pressed, this, [=]() {
        int newWidth = static_cast<int>(startBtn->iconSize().width() *2);
        int newHeight = static_cast<int>(startBtn->iconSize().height() * 2);
        startBtn->setIconSize(QSize(newWidth, newHeight));
        qDebug() << "button size" << startBtn->width();
        qDebug() << "icon size" << startBtn->iconSize().width();
    });
    connect(startBtn, &myButton::released, this, [=]() {
        int newWidth = static_cast<int>(startBtn->iconSize().width() * 0.5);
        int newHeight = static_cast<int>(startBtn->iconSize().height() * 0.5);
        startBtn->setIconSize(QSize(newWidth, newHeight));

        //音效
        QMediaPlayer startplayer;
        startplayer.setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
        startplayer.play();

        QTimer::singleShot(100, this, [=]() {
            chooseScene->setGeometry(this->geometry());//设置初始位置与主页面一致，back不移动
            this->hide();
            chooseScene->show();
        });
    });
    connect(chooseScene, &ChooseLevelScene::chooseSceneBack, this,[=]() {
        this->setGeometry(chooseScene->geometry());
        this->show();
    });
}


void QtCoin::paintEvent(QPaintEvent* ev)
{
    QPainter painterMain(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painterMain.drawPixmap(0, 0, pix);//background

    pix.load(":/res/Title.png");
    pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    qDebug() << "scaled : width : " << pix.width() * 0.5<<"mian window :"<<this->width();
    painterMain.drawPixmap(10,30,pix);

    
}

QtCoin::~QtCoin()
{}

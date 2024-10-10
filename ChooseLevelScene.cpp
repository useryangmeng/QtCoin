#include "ChooseLevelScene.h"
#include <QPixmap>
#include <QMenu>
#include <QMainWindow>
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QMediaPlayer>

#include "myButton.h"

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
	: QMainWindow(parent)
{
	this->setFixedSize(320, 588);
	this->setWindowIcon(QPixmap(":/res/Coin0001"));
	this->setWindowTitle("选择关卡");

	QMenuBar* bar = this->menuBar();
	this->setMenuBar(bar);
	QMenu* startMenu = bar->addMenu("开始");
	QAction* quitAction = startMenu->addAction("退出");
	connect(quitAction, &QAction::triggered, this, &QMainWindow::close);

	myButton* closeBtn = new myButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
	closeBtn->setParent(this);
	closeBtn->move(this->width() - closeBtn->width(), this->height() - closeBtn->height());


	//点击返回触发信号 back
	connect(closeBtn, &myButton::clicked, this, [=]() {
		QTimer::singleShot(100, this, [=]() {
			this->hide();
			emit this->chooseSceneBack();
		});
	});

	// 创建关卡按钮
	for (int i = 0; i < 20; i++)
	{
		myButton* menuBtn = new myButton(":/res/LevelIcon.png","");
		menuBtn->setParent(this);
		menuBtn->move(25 + (i % 4) * 70, 130 + (i / 4) * 70);

		//按钮上显示的文字
		QLabel* label = new QLabel;
		label->setParent(this);
		label->setFixedSize(menuBtn->width(), menuBtn->height());
		label->setText(QString::number(i + 1));
		label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter); //设置居中
		label->move(25 + (i % 4) * 70, 130 + (i / 4) * 70);
		label->setAttribute(Qt::WA_TransparentForMouseEvents, true);  //鼠标事件穿透

		connect(menuBtn, &myButton::clicked, this, [=]() {
			if (pScene == NULL)
			{
				this->hide();
				pScene = new PlayScene(i + 1);
				pScene->setGeometry(this->geometry());
				pScene->show();
				connect(pScene, &PlayScene::chooseSceneBack, this, [=]() {
					this->setGeometry(pScene->geometry());
					this->show();
					delete pScene;
					pScene = NULL;
				});
			}
		});
		
	}

}

void ChooseLevelScene::paintEvent(QPaintEvent* ev)
{
	QPainter painter(this);
	QPixmap pix;
	pix.load(":/res/OtherSceneBg.png");
	painter.drawPixmap(0,0,pix);

	pix.load(":/res/Title.png");
	painter.drawPixmap((this->width()*0.5-pix.width()*0.5),30,pix.width(),pix.height(),pix);
}

ChooseLevelScene::~ChooseLevelScene()
{}

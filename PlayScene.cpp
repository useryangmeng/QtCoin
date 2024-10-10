#include "PlayScene.h"
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QMediaPlayer>

#include "myButton.h"
#include "myCoin.h"
#include "dataconfig.h"

PlayScene::PlayScene(QWidget *parent)
	: QMainWindow(parent)
{
	levalIndex = 0;
}

PlayScene::PlayScene(int indx)
{
	this->levalIndex = indx;
	this->setFixedSize(320, 588);
	this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
	this->setWindowTitle("翻金币");

	QMenuBar* bar = this->menuBar();
	this->setMenuBar(bar);
	QMenu* startMenu = bar->addMenu("开始");
	QAction* quitAction = startMenu->addAction("退出");
	connect(quitAction, &QAction::triggered, this, &QMainWindow::close);

	myButton* closeBtn = new myButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
	closeBtn->setParent(this);
	closeBtn->move(this->width() - closeBtn->width(), this->height() - closeBtn->height());

	//返回按钮功能实现
	connect(closeBtn, &myButton::clicked, [=]() {
		QTimer::singleShot(100, this, [=]() {
			this->hide();
			//触发自定义信号，关闭自身，该信号写到 signals下做声明
			emit this->chooseSceneBack();
		});
	});
	//当前关卡标题
	QLabel* label = new QLabel;
	label->setParent(this);
	QFont font;
	font.setFamily("华文新魏");
	font.setPointSize(20);
	label->setFont(font);
	QString str = QString("Leavel: %1").arg(this->levalIndex);
	label->setText(str);
	label->setGeometry(QRect(30, this->height() - 50, 120, 50)); //设置大小和位置

	dataConfig* config = new dataConfig();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			gameArray[i][j] = (*config).mData[this->levalIndex][i][j];
		}
	}

	coinplayer = new QMediaPlayer(this);
	coinplayer->setSource(QUrl::fromLocalFile(":/res/ConFlipSound.wav"));
	
	//winplayer = new QMediaPlayer(this);
	//// 设置音频文件来源
	//winplayer->setSource(QUrl::fromLocalFile(":/res/LevelWinSound.wav"));
	//// 播放音频
	//winplayer->play();

	//创建金币的背景图片
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//绘制背景图片
			QLabel* label = new QLabel;
			label->setGeometry(0, 0, 50, 50);
			label->setPixmap(QPixmap(":/res/BoardNode.png"));
			label->setParent(this);
			label->move(57 + i * 50, 200 + j * 50);

			//金币对象
			QString img;
			if (gameArray[i][j] == 1)
			{
				img = ":/res/Coin0001.png";
			}
			else
			{
				img = ":/res/Coin0008.png";
			}
			myCoin* coin = new myCoin(img);
			coin->setParent(this);
			coin->move(59 + i * 50, 204 + j * 50);
			coin->posX = i; //记录x坐标
			coin->posY = j; //记录y坐标
			coin->flag = gameArray[i][j]; //记录正反标志

			coinBtn[i][j] = coin;

			connect(coin, &QPushButton::clicked, this, [=]() {
				//coinplayer.play();//音效
				coin->changeFlag();
				gameArray[i][j] = gameArray == 0 ? 1 : 0;

				QTimer::singleShot(300, this, [=]() {
					if (coin->posX + 1 <= 3)
					{
						coinBtn[coin->posX + 1][coin->posY]->changeFlag();
						gameArray[coin->posX + 1][coin->posY] = gameArray[coin->posX + 1][coin->posY] == 0 ? 1 : 0;
					}
					if (coin->posX - 1 >= 0)
					{
						coinBtn[coin->posX - 1][coin->posY]->changeFlag();
						gameArray[coin->posX - 1][coin->posY] = gameArray[coin->posX - 1][coin->posY] == 0 ? 1 : 0;
					}
					if (coin->posY + 1 <= 3)
					{
						coinBtn[coin->posX][coin->posY + 1]->changeFlag();
						gameArray[coin->posX][coin->posY + 1] = gameArray[coin->posX][coin->posY + 1] == 0 ? 1 : 0;
					}
					if (coin->posY - 1 >= 0)
					{
						coinBtn[coin->posX][coin->posY - 1]->changeFlag();
						gameArray[coin->posX][coin->posY - 1] = gameArray[coin->posX][coin->posY - 1] == 0 ? 1 : 0;
					}
					this->isWin = true;
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 4; j++)
						{
							if (coinBtn[i][j]->flag == false)
							{
								this->isWin = false;
								break;
							}
						}
						if (!this->isWin)
						{
							break;
						}
					}
					qDebug() << gameArray;
					qDebug() << "this is win" << this->isWin;
					if (this->isWin)
					{
						//winplayer.play();//音效
						QLabel* winLabel = new QLabel;
						QPixmap tmpPix;
						bool ret = tmpPix.load(":/res/LevelCompletedDialogBg.png");
						if (!ret)
						{
							qDebug() << "加载胜利图片失败";
						}
						winLabel->setGeometry(0, 0, tmpPix.width(), tmpPix.height());
						winLabel->setPixmap(tmpPix);
						winLabel->setParent(this);
						winLabel->move((this->width() - tmpPix.width()) * 0.5, -tmpPix.height());

						winLabel->show();

						qDebug() << "胜利";
						QPropertyAnimation* animation1 = new QPropertyAnimation(winLabel, "geometry");
						animation1->setDuration(1000);
						animation1->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
						animation1->setEndValue(QRect(winLabel->x(), winLabel->y() + 114, winLabel->width(), winLabel->height()));
						animation1->setEasingCurve(QEasingCurve::OutBounce);
						animation1->start();
						qDebug() << "over";

						QTimer::singleShot(1000, this, [=]() {
							this->hide();
							emit this->chooseSceneBack();
						});
					}
				});
			});
		}
	}
	
	




}

void PlayScene::paintEvent(QPaintEvent* ev)
{
	QPainter painter(this);
	QPixmap pix;
	pix.load(":/res/PlayLevelSceneBg.png");
	painter.drawPixmap(0, 0,this->width(),this->height(), pix);

	pix.load(":/res/Title.png");
	pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
	painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);
}

PlayScene::~PlayScene()
{}

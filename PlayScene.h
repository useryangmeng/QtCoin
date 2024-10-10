#pragma once

#include <QMainWindow>
#include <QMediaPlayer>

#include "myCoin.h"

class PlayScene  : public QMainWindow
{
	Q_OBJECT

public:
	PlayScene(QWidget *parent);
	PlayScene(int);
	~PlayScene();

	void paintEvent(QPaintEvent*);

signals:
	void chooseSceneBack();

private:
	int levalIndex;
	int gameArray[4][4];
	myCoin* coinBtn[4][4];
	bool isWin = true;
	QMediaPlayer* coinplayer;
	QMediaPlayer* winplayer;
};

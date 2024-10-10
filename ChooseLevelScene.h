#pragma once

#include <QMainWindow>

#include "PlayScene.h" 

class ChooseLevelScene  : public QMainWindow
{
	Q_OBJECT

public:
	ChooseLevelScene(QWidget *parent = NULL);
	~ChooseLevelScene();

	void paintEvent(QPaintEvent*);


signals:
	void chooseSceneBack();


private:
	PlayScene* pScene = NULL;
};

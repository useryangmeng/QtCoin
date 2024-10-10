#pragma once

#include <QPushButton>


class myButton :
    public QPushButton
{
    Q_OBJECT
public:
    explicit myButton(QWidget* parent = NULL);
    myButton(QString normalImg, QString pressedImg);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

signals:


private:
    QString normalImgPath;
    QString PressedImgPath;

};


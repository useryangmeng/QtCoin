#include "QtCoin.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtCoin w;
    w.show();
    return a.exec();
}

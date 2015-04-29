#include "eswindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ESWindow w;

    return a.exec();
}

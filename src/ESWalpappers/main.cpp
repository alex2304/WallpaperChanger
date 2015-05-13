#include "eswindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("libs");
    paths.append("./libs");
    QCoreApplication::setLibraryPaths(paths);

    QApplication a(argc, argv);
    ESWindow w;

    return a.exec();
}

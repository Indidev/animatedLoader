#include "LoadingWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoadingWindow w;
    w.show();

    w.start();

    return a.exec();
}

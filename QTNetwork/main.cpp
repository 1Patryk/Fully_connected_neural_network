#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow x;
    x.resize(300, 300);
    x.show();
    return a.exec();
}

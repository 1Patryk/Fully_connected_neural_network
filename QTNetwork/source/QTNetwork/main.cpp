#include "mainwindow.h"

#include <QApplication>

#include "../../../include/Fully_connected_network.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Fully_connected_network NETWORK;

    NETWORK.Calculating_the_network_MLP();

    return a.exec();
}

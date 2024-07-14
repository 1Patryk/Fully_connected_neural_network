#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "../../../include/Fully_connected_network.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Fully_connected_network NETWORK;

    std::string Open_filename = {"C:/Users/patry/Desktop/GitHub/Fully_connected_neural_network/Data/Add_1000.txt"};
    NETWORK.Calculating_the_network_MLP(&Open_filename);
}


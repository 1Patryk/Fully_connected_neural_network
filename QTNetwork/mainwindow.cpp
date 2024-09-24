#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QFile>

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

void MainWindow::on_pushButton_settings_clicked()
{
    qDebug() << "You pressed settings button";
}

void MainWindow::on_pushButton_clicked()
{
    QFile file("Add_1000.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        ui->textEdit->setText("Nie znaleziono pliku z pytaniami.");
    }
    else
    {
        QString line;
        QTextStream stream(&file);
        while(!stream.atEnd())
        {
            line=stream.readLine();
            ui->textEdit->setText(line);
        }
    }
    file.close();
}


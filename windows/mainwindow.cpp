#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(Service& service, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _service(service)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_AddNew_clicked()
{

}


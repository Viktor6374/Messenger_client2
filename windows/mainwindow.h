#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./services/service.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Service& service, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_AddNew_clicked();

private:
    Ui::MainWindow *ui;
    Service _service;
};
#endif // MAINWINDOW_H

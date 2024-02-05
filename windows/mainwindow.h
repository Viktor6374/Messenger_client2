#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMutex>
#include "../services/service.h"
#include "../Threads/response_listener.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Service * service, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_AddNew_clicked();

    void on_SendButton_clicked();

    void on_OpenChat_clicked();
public slots:
    void change_filling();
    void set_service(Service * service);

private:
    Ui::MainWindow *ui;
    Service * _service;
    void checking_operation_execution(bool result);
};
#endif // MAINWINDOW_H

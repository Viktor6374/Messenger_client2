#include "./windows/mainwindow.h"
#include "./windows/authorization.h"
#include "./connections/initializer.h"
#include "./services/service.h"
#include "./Threads/response_listener.h"
#include <QApplication>
#include <QDialog>
#include <iostream>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try{
        QString login;
        QString password;
        Authorization dial(&login, &password);
        dial.setWindowTitle("Login");
        dial.exec();

        Initializer init(QHostAddress::LocalHost, 9000);
        std::pair<Service *, Response_listener *> service_and_listener = init.initialize(login, password);
        Service * service = service_and_listener.first;
        Response_listener * listener = service_and_listener.second;
        MainWindow w(*service);

        QObject::connect(listener, SIGNAL(change_filling()), &w, SLOT(change_filling()));
        listener->start();
        w.show();
    }
    catch(std::exception e)
    {
        QMessageBox error;
        error.setWindowTitle("Error");
        error.setText(e.what());
        return error.exec();
    }

    return a.exec();
}

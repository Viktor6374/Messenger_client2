#include "./windows/mainwindow.h"
#include "./windows/authorization.h"
#include "./connections/initializer.h"
#include "./services/service.h"
#include "./Threads/response_listener.h"
#include "./connections/requestfactory.h"
#include <QApplication>
#include <QDialog>
#include <iostream>
#include <QMessageBox>
#include <QCoreApplication>
#include <Windows.h>
#include <QDebug>
#include <DbgHelp.h>
#include "dbgcrash.h"

int main(int argc, char *argv[])
{
//    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
    qRegisterMetaType<Interlocutor>("Interlocutor");
    qRegisterMetaType<Message>("Message");
    QApplication a(argc, argv);
    try{
        QString login;
        QString password;
        Authorization dial(&login, &password);
        dial.setWindowTitle("Login");
        dial.exec();

//        Initializer init(QHostAddress::LocalHost, 9000);
//        std::pair<Service *, Response_listener *> service_and_listener = init.initialize(login, password);

        Service * service = new Service;
        Response_listener * listener = new Response_listener(QHostAddress::LocalHost, 9000, login, password, service);
        listener->start();

        MainWindow w(service);


        QObject::connect(service, SIGNAL(change_filling()), &w, SLOT(change_filling()));
        QObject::connect(service, SIGNAL(add_new_chat_request(QString)), listener, SLOT(add_new_chat(QString)));
        QObject::connect(service, SIGNAL(send_message_request(Message,QString)), listener, SLOT(send_message(Message,QString)));
        QObject::connect(listener, SIGNAL(send_message_response(Message,QString)), service, SLOT(set_answer_send_message(Message,QString)));
        QObject::connect(listener, SIGNAL(add_new_chat_response(Interlocutor)), service, SLOT(set_answer_add_new_chat(Interlocutor)));
        QObject::connect(listener, SIGNAL(new_message(Message)), service, SLOT(set_new_message(Message)));
        w.show();
        listener->do_read();
        service->change_filling();

        return a.exec();
    }
    catch(std::exception e)
    {
        QMessageBox error;
        error.setWindowTitle("Error");
        error.setText(e.what());
        return error.exec();
    }
}

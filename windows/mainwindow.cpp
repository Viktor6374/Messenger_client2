#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "./add_new_chat.h"
#include <QMessageBox>
#include <QTextEdit>
#include <QListWidget>
#include <QLabel>
#include <QListWidgetItem>
#include <QException>
#include <QStringBuilder>

MainWindow::MainWindow(Service * service, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _service = service;
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_AddNew_clicked()
{
    QString username;
    Add_new_chat window(&username);
    window.setWindowTitle("Who do you want to communicate with?");
    window.exec();

    if (_service->find_interlocutor_by_username(username) != nullptr){
        for (int i = 0; i < _service->number_of_interlocutors(); i++){
            if (_service->get_interlocutor(i).get_username() == username){
                _service->set_selected_interlocutor(i);
                change_filling();
                return;
            }
        }
    }

    bool result = _service->add_new_chat(username);

    checking_operation_execution(result);
}

void MainWindow::on_SendButton_clicked()
{
    QTextEdit * text_edit = this->findChild<QTextEdit*>("TextInput");
    QString message = text_edit->toPlainText();
    text_edit->clear();


    bool result = _service->send_message(message);

    checking_operation_execution(result);
}

void MainWindow::on_OpenChat_clicked()
{
    int size = this->findChild<QListWidget*>("Contacts")->count();
    int index = this->findChild<QListWidget*>("Contacts")->currentRow();

    if (index == -1){
        return;
    }

    _service->set_selected_interlocutor(size - 1 - index);
    change_filling();
}

void MainWindow::set_service(Service * service)
{
    _service = service;
}

void MainWindow::change_filling()
{
    qDebug() << "begin change filling";
    try{
        QListWidget * contacts = this->findChild<QListWidget*>("Contacts");
        contacts->clear();
        for (int i = _service->number_of_interlocutors() - 1; i >=0; i--){
            Interlocutor cur_interlocutor = _service->get_interlocutor(i);
            QLabel * label = new QLabel("Username: " + cur_interlocutor.get_username()
                                       + "\nName: " + cur_interlocutor.get_first_name()
                                       + "\nSurname: " + cur_interlocutor.get_second_name());
            QListWidgetItem *item = new QListWidgetItem();

            item->setSizeHint(QSize(contacts->width(), 50));

            contacts->addItem(item);
            contacts->setItemWidget(item, label);
            if (_service->get_selected_interlocutor() != nullptr){
                if (cur_interlocutor == *(_service->get_selected_interlocutor())){
                    item->setBackground(Qt::yellow);
                }
            }
        }
        contacts->update();
    }
    catch(std::exception e)
    {
        qDebug() << e.what();
    }
    QListWidget * chat = this->findChild<QListWidget*>("Chat");
    if(_service->get_selected_interlocutor() == nullptr){
        return;
    }
    chat->clear();

    History_messaging history = _service->get_selected_interlocutor()->get_history_messaging();
    history.reset_counter();
    qDebug() << "begin draw chat:" << history.get_quantity_messages() << "messages";
    for (int i = 0; i < history.get_quantity_messages(); i++){
        qDebug() << "draw" << i << "message";
        Message mess = history.get_next_message();

        QString builder;
        builder = "Sender: " % mess.get_sender_username() % " Time: " % mess.get_send_time().toString();
        QStringList str_list = mess.get_message().split("\n");
        for (int i = 0; i < str_list.size(); i++){
            builder = builder % "\n\t";
            builder = builder % str_list[i];
        }

        QLabel * label = new QLabel(builder);
        QListWidgetItem *item = new QListWidgetItem();

        item->setSizeHint(QSize(chat->width(), 15 + 15 * str_list.size()));

        chat->addItem(item);
        chat->setItemWidget(item, label);
    }
    chat->update();
}

void MainWindow::checking_operation_execution(bool result)
{
    if (result){
        QMessageBox error;
        error.setWindowTitle("Error");
        error.setText("The server is not responding");
        error.exec();
    }
}


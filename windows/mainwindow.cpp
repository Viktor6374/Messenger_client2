#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "./add_new_chat.h"
#include <QMessageBox>
#include <QTextEdit>
#include <QListWidget>
#include <QLabel>
#include <QListWidgetItem>

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
    QMutexLocker locker(&mutex);
    QString username;
    Add_new_chat window(&username);
    window.setWindowTitle("Who do you want to communicate with?");
    window.exec();

    locker.unlock();

    bool result = _service.add_new_chat(username);

    checking_operation_execution(result);
}

void MainWindow::on_SendButton_clicked()
{
    QMutexLocker locker(&mutex);
    QTextEdit * text_edit = this->findChild<QTextEdit*>("TextInput");
    QString message = text_edit->toPlainText();
    text_edit->clear();

    locker.unlock();

    bool result = _service.send_message(message);

    checking_operation_execution(result);
}

void MainWindow::on_OpenChat_clicked()
{
    QMutexLocker locker(&mutex);
    int index = this->findChild<QListWidget*>("Contacts")->currentRow();
    _service.set_selected_interlocutor(index);
    change_filling();
}

void MainWindow::change_filling()
{
    QMutexLocker locker(&mutex);
    QListWidget * contacts = this->findChild<QListWidget*>("Contacts");
    contacts->clear();
    for (int i = _service.number_of_interlocutors() - 1; i >=0; i--){
        Interlocutor cur_interlocutor = _service[i];
        QLabel * label = new QLabel("Username: " + cur_interlocutor.get_username()
                                   + "/nName: " + cur_interlocutor.get_first_name()
                                   + "/nSurname" + cur_interlocutor.get_second_name());
        QListWidgetItem *item = new QListWidgetItem();
        contacts->addItem(item);
        contacts->setItemWidget(item, label);

        if (cur_interlocutor == *(_service.get_selected_interlocutor())){
            item->setBackground(Qt::yellow);
        }
    }

    contacts->show();

    QListWidget * chat = this->findChild<QListWidget*>("Chat");

    if(_service.get_selected_interlocutor() == nullptr){
        return;
    }

    History_messaging history = _service.get_selected_interlocutor()->get_history_messaging();
    history.reset_counter();

    for (int i = 0; i < history.get_quantity_messages(); i++){
        Message mess = history.get_next_message();
        QLabel * label = new QLabel("Sender: " + mess.get_sender_username()
                                   + "Time: " + mess.get_send_time().toString()
                                   + "/n/t" + mess.get_message());
        QListWidgetItem *item = new QListWidgetItem();
        chat->addItem(item);
        chat->setItemWidget(item, label);
    }

    chat->show();
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


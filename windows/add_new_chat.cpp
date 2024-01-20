#include "add_new_chat.h"
#include "ui_add_new_chat.h"
#include <QLineEdit>

Add_new_chat::Add_new_chat(QString * username, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_new_chat)
{
    ui->setupUi(this);
    _username = username;
}

Add_new_chat::~Add_new_chat()
{
    delete ui;
}

void Add_new_chat::on_ok_button_clicked()
{
    *_username = this->findChild<QLineEdit*>("username_lineEdit")->text();
    this->close();
}


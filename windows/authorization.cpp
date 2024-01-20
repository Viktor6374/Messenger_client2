#include "authorization.h"
#include "ui_authorization.h"
#include <QLineEdit>

Authorization::Authorization(QString * login, QString * password, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Authorization)
{
    ui->setupUi(this);
    _login = login;
    _password = password;
}

Authorization::~Authorization()
{
    delete ui;
}

void Authorization::on_login_button_clicked()
{
    *_login = this->findChild<QLineEdit*>("login_lineEdit")->text();
    *_password = this->findChild<QLineEdit*>("password_lineEdit")->text();
    this->close();
}


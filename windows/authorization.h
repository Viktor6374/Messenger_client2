#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QDialog>
#include <QString>

namespace Ui {
class Authorization;
}

class Authorization : public QDialog
{
    Q_OBJECT

public:
    explicit Authorization(QString * login, QString * password, QWidget *parent = nullptr);
    ~Authorization();

private slots:
    void on_login_button_clicked();

private:
    Ui::Authorization *ui;
    QString * _login;
    QString * _password;
};

#endif // AUTHORIZATION_H

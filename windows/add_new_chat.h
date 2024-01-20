#ifndef ADD_NEW_CHAT_H
#define ADD_NEW_CHAT_H

#include <QDialog>
#include <QString>

namespace Ui {
class Add_new_chat;
}

class Add_new_chat : public QDialog
{
    Q_OBJECT

public:
    explicit Add_new_chat(QString * username, QWidget *parent = nullptr);
    ~Add_new_chat();

private slots:
    void on_ok_button_clicked();

private:
    Ui::Add_new_chat *ui;
    QString * _username;
};

#endif // ADD_NEW_CHAT_H

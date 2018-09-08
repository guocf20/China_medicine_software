#include "dialog.h"
#include "ui_dialog.h"
#include <QString>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->passwd->setEchoMode(QLineEdit::Password);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_confirm_button_clicked()
{
    QString username;
    QString passwd;
    passwd = this->ui->passwd->text();
    username = this->ui->user_name->text();
    QMessageBox::information(NULL, "Title", passwd, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    accept();
}

void Dialog::on_pushButton_2_clicked()
{
    reject();
}

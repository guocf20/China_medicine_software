#include<QFile>
#include <QString>
#include <QMessageBox>
#include "login_dialog.h"
#include "ui_login_dialog.h"
#include "com_define.h"
#include "change_pwd_dialog.h"
#include <QCryptographicHash>
#include<QDebug>
#include <string.h>

Login_Dialog::Login_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login_Dialog)
{
    ui->setupUi(this);
    ui->passwd->setEchoMode(QLineEdit::Password);
    this->setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    this->setWindowTitle(SOFT_NAME);
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
                QBrush(QPixmap(":/images/backgroud.jpg").scaled(// 缩放背景图.
                    this->size(),
                    Qt::IgnoreAspectRatio,
                    Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    this->setPalette(palette);
}

Login_Dialog::~Login_Dialog()
{
    delete ui;
}

int check_valid_user(QString user_name, QString passwd)
{
    QFile passfile(PASSWD);
    char save_pass_hash[256] = {'\0'};

    passfile.open(QIODevice::ReadOnly);
    passfile.read(save_pass_hash, 255);
    passfile.close();

    if(user_name.isEmpty() || passwd.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("告警");
        msgBox.setText("密码或账号不能为空");
        msgBox.exec();
        return 1;
    }

    QByteArray passwd_hash;
    passwd_hash = QCryptographicHash::hash(passwd.toLatin1(), QCryptographicHash::Md5);
    QMessageBox msgbox;

    qDebug()<<passwd_hash.toHex()<<"++++";
    qDebug()<<save_pass_hash;

    if(qstrcmp(save_pass_hash, passwd_hash.toHex()) != 0)
    {
          msgbox.setText("密码错误");
          msgbox.resize(100,100);
          msgbox.exec();
          return 1;
    }

    return 0;
}

void Login_Dialog::on_login_clicked()
{

QString username;
QString passwd;
passwd = this->ui->passwd->text();
username = this->ui->user_name->text();
if(check_valid_user(username, passwd) == 0)
{
    accept();
}
}


void Login_Dialog::on_pushButton_clicked()
{
    Change_Pwd_Dialog *pwd_win = new Change_Pwd_Dialog;

    pwd_win->exec();
    reject();
}

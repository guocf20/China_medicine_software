#include<QString>
#include<QMessageBox>
#include<QDebug>
#include<QFile>
#include<QDir>
#include<QCryptographicHash>
#include "change_pwd_dialog.h"
#include "ui_change_pwd_dialog.h"
#include "com_define.h"


Change_Pwd_Dialog::Change_Pwd_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Change_Pwd_Dialog)
{
    ui->setupUi(this);
    this->setTabOrder(ui->old_pwd, ui->new_pwd);
    this->setTabOrder(ui->new_pwd, ui->confirm);
    this->setTabOrder(ui->confirm,ui->pushButton);
    ui->confirm->setEchoMode(QLineEdit::Password);
    ui->old_pwd->setEchoMode(QLineEdit::Password);
    ui->new_pwd->setEchoMode(QLineEdit::Password);

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

Change_Pwd_Dialog::~Change_Pwd_Dialog()
{
    delete ui;
}

void Change_Pwd_Dialog::on_pushButton_clicked()
{
    QString old_pwd;
    QString new_pwd;
    QString confirm;

    QFile passfile(PASSWD);
    char save_pass_hash[256] = {'\0'};

    passfile.open(QIODevice::ReadOnly);
    passfile.read(save_pass_hash, 255);
    passfile.close();


    old_pwd = this->ui->old_pwd->text();
    new_pwd = this->ui->new_pwd->text();
    confirm = this->ui->confirm->text();
    qDebug()<<qPrintable(old_pwd);
    qDebug()<<qPrintable(confirm);

    QByteArray passwd_hash;
    passwd_hash = QCryptographicHash::hash(old_pwd.toLatin1(), QCryptographicHash::Md5);


    if (qstrcmp(save_pass_hash,passwd_hash.toHex()) != 0)
    {
       qDebug()<<QDir::currentPath();
       qDebug()<<"input_passwd"<<passwd_hash.toHex()<<"old"<<old_pwd;
       qDebug()<<"save_pwd"<<save_pass_hash;
       QMessageBox msgbox;
       msgbox.setText("旧密码验证错误");
       msgbox.exec();
       return;
    }

    if(new_pwd.isEmpty() || old_pwd.isEmpty())
    {
        QMessageBox msgbox;
        msgbox.setText("新密码不能为空");
        msgbox.exec();
        return;
    }

    if(new_pwd != confirm)
    {
       this->ui->old_pwd->clear();
       this->ui->new_pwd->clear();
       this->ui->confirm->clear();
       QMessageBox msgbox;
       msgbox.setText("新密码不一致");
       msgbox.exec();
       return;
    }
    else
    {
        QByteArray new_passwd_hash;
        new_passwd_hash = QCryptographicHash::hash(new_pwd.toLatin1(), QCryptographicHash::Md5);

        qDebug()<<new_passwd_hash.toHex();

        QFile file(PASSWD);
        file.open(QIODevice::Truncate|QIODevice::WriteOnly);
        file.close();

        file.open(QIODevice::ReadWrite);
        file.write(new_passwd_hash.toHex(),strlen(new_passwd_hash.toHex()));
        file.close();

        QMessageBox msgbox;
        msgbox.setText("修改成功");
        msgbox.exec();
    }

}

void Change_Pwd_Dialog::on_radioButton_toggled(bool checked)
{
    qDebug()<<"here";
    if(this->ui->radioButton->isChecked())
    {
        qDebug()<<"checked";
        this->ui->confirm->setEchoMode(QLineEdit::Normal);
        this->ui->new_pwd->setEchoMode(QLineEdit::Normal);
        this->ui->old_pwd->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        qDebug()<<"unchecked";

        this->ui->confirm->setEchoMode(QLineEdit::Password);
        this->ui->new_pwd->setEchoMode(QLineEdit::Password);
        this->ui->old_pwd->setEchoMode(QLineEdit::Password);
    }
}

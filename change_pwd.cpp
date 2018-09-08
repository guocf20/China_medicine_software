#include "change_pwd.h"
#include "ui_change_pwd.h"

Change_Pwd::Change_Pwd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Change_Pwd)
{
    ui->setupUi(this);
    //this->setWindowFlags(Qt::WindowStaysOnTopHint);
}

Change_Pwd::~Change_Pwd()
{
    delete ui;
}

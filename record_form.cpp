#include "record_form.h"
#include "ui_record_form.h"
#include "com_define.h"
#include "comm_window.h"
#include<table_with_database.h>
#include <QDebug>
#include<QDialogButtonBox>
#include<QDialog>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

extern QSqlDatabase database;

Record_Form::Record_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Record_Form)
{
    ui->setupUi(this);
    this->setWindowTitle(SOFT_NAME);
    this->ui->male->setChecked(true);
}

Record_Form::~Record_Form()
{
    delete ui;
}

void Record_Form::show_with_no_submit()
{
    this->ui->pushButton->hide();
    this->show();
}



void Record_Form::on_pushButton_clicked()
{
    QString name_s = this->ui->name->text();
    QString sex_s;
    QString symptom_s = this->ui->symptom->toPlainText();
    QString pre_s = this->ui->pre->toPlainText();
    QString comm_s = this->ui->comm->toPlainText();
    QString tele_s = this->ui->telephone->text();
    QString date_s = this->ui->visit_time->text();

    if(Comm_window::show_dialog() == 1)
    {
        return;
    }

    if (this->ui->male->isChecked() == true)
    {
        sex_s = QString("男");
        qDebug()<< "male";
    }
    else
    {
        sex_s = QString("女");
        qDebug()<<"female";
    }

    QByteArray name_b = name_s.toLocal8Bit();
    char *name_utf = name_b.data();

    QByteArray sex_b = sex_s.toLocal8Bit();
    char *sex_utf = sex_b.data();

    QByteArray symptom_b = symptom_s.toLocal8Bit();
    char *symptom_utf = symptom_b.data();

    QByteArray pre_b = pre_s.toLocal8Bit();
    char *pre_utf = pre_b.data();

    QByteArray comm_b = comm_s.toLocal8Bit();
    char *comm_utf = comm_b.data();

    QByteArray tele_b = tele_s.toLocal8Bit();
    char *tele_utf = tele_b.data();

    QByteArray date_b = date_s.toLocal8Bit();
    char *date_utf = date_b.data();

    char q_buf[10240] = {'\0'};

    snprintf(q_buf, 10239,  \
    "insert into record_info values(NULL, '%s', '%s','%s', '%s', '%s', '%s','%s')", \
             name_utf, sex_utf, date_utf, tele_utf, symptom_utf, pre_utf, comm_utf);

    QString showsql = QString::fromLocal8Bit(q_buf);

     qDebug()<< showsql;
     QSqlQuery query(database);
     query.exec(showsql);
     query.clear();

}


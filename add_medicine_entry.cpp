#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include<QMessageBox>

#include "add_medicine_entry.h"
#include "ui_add_medicine_entry.h"
#include"com_define.h"

extern QSqlDatabase database;

Add_medicine_entry::Add_medicine_entry(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Add_medicine_entry)
{
    ui->setupUi(this);
    this->setWindowTitle(SOFT_NAME);
}

Add_medicine_entry::~Add_medicine_entry()
{
    delete ui;
}


void Add_medicine_entry::on_add_clicked()
{
    QString name_s = this->ui->name->text();
    QString price_s = this->ui->price->text();
    QString stock_s = this->ui->stock->text();
    QString comm_s = this->ui->comm->text();

    QMessageBox msgbox;
    msgbox.setWindowTitle(SOFT_NAME);

    if(name_s.isEmpty()
       || price_s.isEmpty()
       || stock_s.isEmpty())
    {
        msgbox.setText("除备注外都必须填写");
        msgbox.exec();
        return;
    }


    QByteArray name_b = name_s.toLocal8Bit();
    char *name_utf = name_b.data();

    QByteArray price_b = price_s.toLocal8Bit();
    char *price_utf = price_b.data();

    QByteArray stock_b = stock_s.toLocal8Bit();
    char *stock_utf = stock_b.data();

    QByteArray comm_b = comm_s.toLocal8Bit();
    char *comm_utf = comm_b.data();

    char q_buf[256] = {'\0'};

    snprintf(q_buf,255, "select * from medicine_info where name = '%s'", name_utf);

    QString checksql = QString::fromLocal8Bit(q_buf);

    qDebug()<<checksql;
    QSqlQuery check_query(database);

    bool flag = check_query.exec(checksql);

    int i = 0;
    while(check_query.next())
    {
        i++;
    }

    if( i> 0)
    {
        msgbox.setText(name_s + QString("药物已经录入"));
        msgbox.exec();
        check_query.clear();
        return ;
    }

    snprintf(q_buf, 255, "insert into medicine_info values(NULL, '%s', '%s', '%s', '%s')", \
             name_utf, price_utf, stock_utf, comm_utf);

    QString showsql = QString::fromLocal8Bit(q_buf);

     qDebug()<< showsql;
     QSqlQuery query(database);
     flag = query.exec(showsql);

     if(flag == true)
     {
         msgbox.setText("插入成功");
         msgbox.exec();
     }
     else
     {
         msgbox.setText("插入失败");
         msgbox.exec();
     }

     query.clear();

}

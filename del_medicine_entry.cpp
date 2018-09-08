#include<QDebug>
#include<QDialogButtonBox>
#include<QDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QMessageBox>

#include"com_define.h"
#include "del_medicine_entry.h"
#include "ui_del_medicine_entry.h"


extern QSqlDatabase database;



Del_medicine_entry::Del_medicine_entry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Del_medicine_entry)
{
    ui->setupUi(this);
}

Del_medicine_entry::~Del_medicine_entry()
{
    delete ui;
}


static int show_dialog()
{
   QDialog dialog;
   dialog.setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
   dialog.setWindowTitle(SOFT_NAME);
   QDialogButtonBox *button = new QDialogButtonBox(&dialog);

   button->setContentsMargins(80,30,100,20);
   dialog.resize(300, 100);

   button->addButton("确认", QDialogButtonBox::YesRole);
   button->addButton("取消", QDialogButtonBox::NoRole);
   QObject::connect(button, SIGNAL(accepted()), &dialog, SLOT(accept()));

   QObject::connect(button, SIGNAL(rejected()), &dialog, SLOT(reject()));

   if(dialog.exec() == QDialog::Accepted)
   {

      qDebug()<< "accepted";
      return 0;
   }
   else
   {
       qDebug()<<"canceled";
       return 1;

   }

   return 1;
}

void Del_medicine_entry::on_submit_clicked()
{
   if(show_dialog() != 0)
   {
       return ;
   }


   QString name_s = this->ui->name->text();
   QByteArray name_b = name_s.toLocal8Bit();
   QMessageBox msgBox;
   msgBox.setWindowTitle(SOFT_NAME);

   char *name_utf = name_b.data();

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
   qDebug()<<"result = "<< i;
   if( i== 0)
   {
       msgBox.setText(name_s + QString("药物不存在"));
       msgBox.exec();
       check_query.clear();
       return ;
   }


   snprintf(q_buf, 255, "delete from medicine_info where name = '%s'", name_utf);

   QString showsql = QString::fromLocal8Bit(q_buf);

   qDebug()<< showsql;
   QSqlQuery query(database);
   flag = query.exec(showsql);

   if(flag == true)
   {

       msgBox.setText(QString("删除") + name_s + QString("成功"));
       msgBox.setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
       msgBox.exec();
   }
   else
   {
       QMessageBox msgBox;
       msgBox.setWindowTitle(SOFT_NAME);
       msgBox.setText(QString("删除") + name_s + QString("失败"));
       msgBox.setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
       msgBox.exec();
   }

   query.clear();


   return;
}

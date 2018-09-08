#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QDebug>
#include<QMessageBox>
#include "search_form.h"
#include "ui_search_form.h"
#include "com_define.h"
#include "table_with_database.h"
#include "comm_window.h"


extern QSqlDatabase database;

search_Form::search_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::search_Form)
{
    ui->setupUi(this);
    this->setTabOrder(this->ui->search_name, this->ui->pushButton);
    this->setWindowTitle(SOFT_NAME);
}

search_Form::~search_Form()
{
    delete ui;
}

void search_Form::set_pushButton_text(QString s)
{
    this->ui->pushButton->setText(s);
}

void search_medicine_info(QString medicine_name)
{
   QWidget *win = new QWidget;

   win->setWindowTitle(SOFT_NAME);

   Table_with_database *result_table = new Table_with_database;

   QVBoxLayout *layout = new QVBoxLayout;

   layout->addWidget(result_table);
   win->setLayout(layout);

   result_table->setColumnCount(5);
   QStringList header;
   header<<"编号"<<"名称"<<"单价(克/元)"<<"库存(克)"<<"备注";
   result_table->setHorizontalHeaderLabels(header);


   QByteArray bytes = medicine_name.toLocal8Bit();
   char *utf8 = bytes.data();
   char q_buf[256] = {'\0'};

   snprintf(q_buf, 255, "select *from medicine_info where name = '%s'", utf8);

   QString showsql = QString::fromLocal8Bit(q_buf);


    qDebug()<<medicine_name;
    QSqlQuery query(database);
    query.exec(showsql);
    int i = 0;
    while(query.next())
    {
          i++;
          int row_count = result_table->rowCount();
          result_table->insertRow(row_count);
          QTableWidgetItem *num = new QTableWidgetItem();
          num->setFlags(Qt::NoItemFlags);
          QTableWidgetItem *name = new QTableWidgetItem();
          QTableWidgetItem *price = new QTableWidgetItem();
          QTableWidgetItem *left = new QTableWidgetItem();
          QTableWidgetItem *comm = new QTableWidgetItem();
          num->setText(query.value(0).toString());
          name->setText(query.value(1).toString());
          price->setText(query.value(2).toString());
          left->setText(query.value(3).toString());
          comm->setText(query.value(4).toString());
          result_table->setItem(row_count, 0, num);
          result_table->setItem(row_count, 1, name);
          result_table->setItem(row_count, 2, price);
          result_table->setItem(row_count, 3, left);
          result_table->setItem(row_count, 4, comm);

          qDebug()<<query.value(0).toString();
          qDebug()<<query.value(1).toString();
          qDebug()<<query.value(2).toString();
    }
    if(i == 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("告警");
        msgBox.setText("没找到该药物");
        msgBox.exec();
    }
    else
    {
        QObject::connect(result_table, SIGNAL(cellChanged(int,int)),result_table, SLOT(medicine_info_update_to_database(int, int)));
        win->show();
    }
    query.clear();
}



static void  search_record_info(QString  name_s)
{

    QByteArray name_b = name_s.toLocal8Bit();

    char *name_utf = name_b.data();

    QWidget *medicine_win = new QWidget;

    medicine_win->setWindowTitle(SOFT_NAME);

    Table_with_database *medicine_table = new Table_with_database;

    medicine_table->setMouseTracking(true);
    QVBoxLayout *layout = new QVBoxLayout;

    medicine_table->setColumnCount(8);
    QStringList header;
    header<<"编号"<<"名称"<<"性别"<<"日期"<<"电话"<<"症状"<<"药方"<<"备注";
    medicine_table->setHorizontalHeaderLabels(header);

    layout->addWidget(medicine_table);
    medicine_win->setLayout(layout);

    char q_buf[256] = {'\0'};

    snprintf(q_buf, 255, "select * from record_info where name = '%s' order by visit_time desc, name desc", name_utf);

    QString showsql = QString::fromLocal8Bit(q_buf);
    QSqlQuery query(database);

    bool flag = query.exec(showsql);

    qDebug()<<showsql << (flag == true?"true":"false");

    while(query.next())
    {
        qDebug()<<"in query";
        int row_count = medicine_table->rowCount();
        medicine_table->insertRow(row_count);
        QTableWidgetItem *num = new QTableWidgetItem();
        num->setFlags(Qt::NoItemFlags);
    QTableWidgetItem *name = new QTableWidgetItem();
    QTableWidgetItem *sex = new QTableWidgetItem();
    QTableWidgetItem *date = new QTableWidgetItem();
    QTableWidgetItem *tele = new QTableWidgetItem();
    QTableWidgetItem *sym = new QTableWidgetItem();
    QTableWidgetItem *pre = new QTableWidgetItem();
    QTableWidgetItem *comm = new QTableWidgetItem();

    num->setText(query.value(0).toString());
    name->setText(query.value(1).toString());
    sex->setText(query.value(2).toString());
    date->setText(query.value(3).toString());
    tele->setText(query.value(4).toString());
    sym->setText(query.value(5).toString());
    pre->setText(query.value(6).toString());
    comm->setText(query.value(7).toString());

    medicine_table->setItem(row_count, 0, num);
    medicine_table->setItem(row_count, 1, name);
    medicine_table->setItem(row_count, 2, sex);
    medicine_table->setItem(row_count, 3, date);
    medicine_table->setItem(row_count, 4, tele);
    medicine_table->setItem(row_count, 5, sym);
    medicine_table->setItem(row_count, 6, pre);
    medicine_table->setItem(row_count, 7, comm);

    }
    medicine_table->resizeRowsToContents();
    medicine_table->resizeColumnsToContents();
    query.clear();
    QObject::connect(medicine_table, SIGNAL(cellChanged(int,int)),medicine_table, SLOT(record_form_update_to_database(int, int)));
    QObject::connect(medicine_table, SIGNAL(cellEntered(int,int)), medicine_table, SLOT(show_the_cell_detail(int, int)));
    medicine_win->showMaximized();
}


void search_Form::on_pushButton_clicked()
{
    QString name = this->ui->pushButton->text();

    if( name == QString("检索药品"))
    {
        search_medicine_info(this->ui->search_name->text());
    }
    else if( name == QString("检索病人病历"))
    {
        search_record_info(this->ui->search_name->text());
    }

    else
    {
           ;
    }
}

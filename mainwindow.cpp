#include <QDialog>
#include <QWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QDebug>
#include<QObject>
#include <QMessageBox>
#include<QLineEdit>
#include<QLabel>
#include<QPushButton>
#include<QHeaderView>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "com_define.h"
#include "record_form.h"
#include "search_form.h"
#include "table_with_database.h"
#include "add_medicine_entry.h"
#include "del_medicine_entry.h"

extern QSqlDatabase database;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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


MainWindow::~MainWindow()
{
    delete ui;
}

/*
 *显示所有药品
*/
static void show_all_medicine()
{
    QWidget *medicine_win = new QWidget;

    medicine_win->setWindowTitle(SOFT_NAME);

    Table_with_database *medicine_table = new Table_with_database;
    QVBoxLayout *layout = new QVBoxLayout;

    medicine_table->setColumnCount(5);
    QStringList header;
    header<<"编号"<<"名称"<<"单价(克/元)"<<"库存(克)"<<"备注";
    medicine_table->setHorizontalHeaderLabels(header);
    medicine_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    layout->addWidget(medicine_table);
    medicine_win->setLayout(layout);

    QString showsql = QString("select * from medicine_info order by name");
    QSqlQuery query(database);
    query.exec(showsql);

    while(query.next())
    {
        qDebug()<<"in query";
    int row_count = medicine_table->rowCount();
    medicine_table->insertRow(row_count);
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
    medicine_table->setItem(row_count, 0, num);
    medicine_table->setItem(row_count, 1, name);
    medicine_table->setItem(row_count, 2, price);
    medicine_table->setItem(row_count, 3, left);
    medicine_table->setItem(row_count, 4, comm);
    }
    query.clear();
    QObject::connect(medicine_table, SIGNAL(cellChanged(int,int)),medicine_table, SLOT(medicine_info_update_to_database(int, int)));
    medicine_win->showMaximized();

}

static void recordinfo()
{
    Record_Form *form = new Record_Form;
    form->show();
}


void MainWindow::on_action_search_record_triggered()
{
    QWidget *medicine_win = new QWidget;

    medicine_win->setWindowTitle(SOFT_NAME);

    Table_with_database *medicine_table = new Table_with_database;

    medicine_table->setMouseTracking(true);
    QVBoxLayout *layout = new QVBoxLayout;

    medicine_table->setColumnCount(8);
    QStringList header;
    header<<"编号"<<"名称"<<"性别"<<"日期"<<"电话"<<"症状"<<"药方"<<"备注";
    medicine_table->setHorizontalHeaderLabels(header);
    medicine_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    layout->addWidget(medicine_table);
    medicine_win->setLayout(layout);

    QString showsql = QString("select * from record_info order by visit_time desc, name desc");
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

void MainWindow::on_actionadd_record_triggered()
{
    recordinfo();
}





void MainWindow::on_actiondel_record_triggered()
{
   QMessageBox box;
   box.setWindowTitle(SOFT_NAME);
   box.setText("暂不支持");
   box.exec();
}


void MainWindow::on_show_medicine_triggered()
{
    show_all_medicine();
}



void MainWindow::on_add_medicine_triggered()
{
       Add_medicine_entry *win = new Add_medicine_entry;
       win->show();
}

void MainWindow::on_modify_medicine_triggered()
{
    search_Form *win = new search_Form;
    win->set_pushButton_text("检索药品");
    win->show();
}

void MainWindow::on_del_medicine_triggered()
{
    Del_medicine_entry *win = new Del_medicine_entry;
    win->setWindowTitle(SOFT_NAME);
    win->setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    win->show();
}



void MainWindow::on_actionmodify_record_2_triggered()
{

    search_Form *search = new search_Form;
    search->set_pushButton_text("检索病人病历");
    search->show();
}



void MainWindow::on_actionversion_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(SOFT_NAME);
    msgBox.setText(QString("VERSION ") + QString(SOFT_VER));
    msgBox.exec();
}

void MainWindow::on_actionauthor_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(SOFT_NAME);
    msgBox.setText(QString("姓名：郭成峰 \n") + QString("邮箱: guocf20@163.com"));
    msgBox.exec();
}

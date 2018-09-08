#include "table_with_database.h"
#include<QDebug>
#include<QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QTextEdit>
#include<QToolTip>
#include<QHeaderView>
#include<QByteArray>
#include"com_define.h"


extern QSqlDatabase database;

Table_with_database::Table_with_database()
{

}

void Table_with_database::getItem(QTableWidgetItem *info)
{
    QTableWidgetItem *name_item = this->item(info->row(), 0);
    QMessageBox msgBox;
    msgBox.setWindowTitle("告警");
    msgBox.setText(name_item->text());
    msgBox.exec();

    return ;
}

void Table_with_database::medicine_info_update_to_database(int row, int col)
{
    QTableWidgetItem *id_item = this->item(row, 0);
    QTableWidgetItem *update_item = this->item(row, col);
    QString update_name = update_item->text();
    int uid = id_item->text().toInt();
    const char *column = "unknown";

    switch (col)
    {
       case 1:
        column = "name";
        break;
       case 2:
        column = "price";
        break;
       case 3:
        column = "stock";
        break;
       case 4:
        column = "comm";
        break;
       default:
        column = "unknown";
        break;
    }

    if(strcmp(column, "unknown") == 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("告警");
        msgBox.setText("找不到该信息");
        msgBox.exec();
        return;
    }


    QByteArray bytes = update_name.toLocal8Bit();
    char *utf8 = bytes.data();
    char q_buf[256] = {'\0'};

    snprintf(q_buf, 255, "update medicine_info set %s = '%s' where id = %d", column, utf8, uid);

    QString showsql = QString::fromLocal8Bit(q_buf);

     qDebug()<<q_buf<< showsql;
     QSqlQuery query(database);
     query.exec(showsql);
     query.clear();

    return;
}

void Table_with_database::show_the_cell_detail(int row, int col)
{
       qDebug()<<"detail info";
       QTableWidgetItem *detail_item = this->item(row, col);
       QToolTip::showText(QCursor::pos(), detail_item->text());

}

void Table_with_database::record_form_update_to_database(int row, int col)
{
    QTableWidgetItem *id = this->item(row, 0);

    QString id_s = id->text();

    const char *column = "unknown";

    switch (col)
    {
       case 1:
        column = "name";
        break;
       case 2:
        column = "sex";
        break;
       case 3:
        column = "visit_time";
        break;
       case 4:
        column = "tele";
       case 5:
        column = "symptom";
        break;
       case 6:
        column = "prescription";
        break;
       case 7:
        column = "comm";
        break;

       default:
        column = "unknown";
        break;
    }

    if(strcmp(column, "unknown") == 0)
    {
        QMessageBox msgbox;
        msgbox.setWindowTitle(SOFT_NAME);
        msgbox.setText("编号无法变更");
        msgbox.exec();
        return;
    }

    qDebug()<<"update info";
    QTableWidgetItem *detail_item = this->item(row, col);

    QString entry_s = detail_item->text();
    QByteArray entry_b = entry_s.toLocal8Bit();
    char *entry_utf = entry_b.data();



    char q_buf[256] = {'\0'};

    snprintf(q_buf, 255, "update record_info set %s = '%s' where id = %d", column, entry_utf, id_s.toInt());

    QString showsql = QString::fromLocal8Bit(q_buf);

     qDebug()<<showsql;
     QSqlQuery query(database);
     query.exec(showsql);
     query.clear();
     this->resizeRowsToContents();
     this->resizeColumnsToContents();
}

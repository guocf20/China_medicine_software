#ifndef TABLE_WITH_DATABASE_H
#define TABLE_WITH_DATABASE_H

#include <QObject>
#include<QTableWidget>
#include<QTableWidgetItem>
#include<QTextEdit>
#include<QEvent>

class Table_with_database:public QTableWidget
{
    Q_OBJECT
public:
    Table_with_database();
public slots:
    void getItem(QTableWidgetItem *info);
    void medicine_info_update_to_database(int row, int col);
    void record_form_update_to_database(int row, int col);
    void show_the_cell_detail(int row, int col);
private:
    QTextEdit detail;
};

#endif // TABLE_WITH_DATABASE_H

#ifndef M_SQL_H
#define M_SQL_H

#include<QObject>
#include<QTableWidgetItem>

class M_SQL: public QObject
{
    Q_OBJECT
public:
    M_SQL();
public slots:
    void getItem(QTableWidgetItem *);

};

#endif // M_SQL_H

#include "m_sql.h"
#include <QMessageBox>
#include<QDebug>

M_SQL::M_SQL()
{

}

void M_SQL::getItem(QTableWidgetItem *info)
{
    int col = info->column();
    int row = info->row();
    qDebug()<<col << "+" << row;
    QString str = info->text();
    QMessageBox msgBox;
    msgBox.setWindowTitle("告警");
    msgBox.setText(str);
    msgBox.exec();
    return ;
}

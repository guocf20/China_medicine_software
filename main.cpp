#include "mainwindow.h"
#include <QApplication>
#include "login_dialog.h"
#include "change_pwd.h"
#include "com_define.h"
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>


QSqlDatabase database;

void init()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(M_DATA_BASE);
    bool ok = database.open();

    if(ok)
    {
        qDebug()<<"open success";
    }
    else
    {
        qDebug()<<"open failed";
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    Login_Dialog q;
    int result;
    result = q.exec();
    qDebug()<<"q.exec()";

    while(result == QDialog::Rejected)
    {
        qDebug()<<"rejected";
         result = q.exec();
    }

    if(result == QDialog::Accepted)
    {
        init();
        w.show();
        return a.exec();
    }
    else if(result == QDialog::Rejected)
    {
        return a.exec();
    }
    else
    {
        return 0;
    }
}

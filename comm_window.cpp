#include "comm_window.h"
#include<QDebug>
#include<QDialog>
#include<QDialogButtonBox>
#include<QObject>
#include"com_define.h"

Comm_window::Comm_window()
{

}

int Comm_window::show_dialog()
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

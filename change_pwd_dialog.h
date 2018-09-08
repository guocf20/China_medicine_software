#ifndef CHANGE_PWD_DIALOG_H
#define CHANGE_PWD_DIALOG_H

#include <QDialog>

namespace Ui {
class Change_Pwd_Dialog;
}

class Change_Pwd_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Change_Pwd_Dialog(QWidget *parent = nullptr);
    ~Change_Pwd_Dialog();

private slots:
    void on_pushButton_clicked();

    void on_radioButton_toggled(bool checked);

private:
    Ui::Change_Pwd_Dialog *ui;
};

#endif // CHANGE_PWD_DIALOG_H

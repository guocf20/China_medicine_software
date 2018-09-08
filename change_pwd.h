#ifndef CHANGE_PWD_H
#define CHANGE_PWD_H

#include <QWidget>

namespace Ui {
class Change_Pwd;
}

class Change_Pwd : public QWidget
{
    Q_OBJECT

public:
    explicit Change_Pwd(QWidget *parent = nullptr);
    ~Change_Pwd();

private:
    Ui::Change_Pwd *ui;
};

#endif // CHANGE_PWD_H

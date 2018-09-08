#ifndef ADD_MEDICINE_ENTRY_H
#define ADD_MEDICINE_ENTRY_H

#include <QWidget>

namespace Ui {
class Add_medicine_entry;
}

class Add_medicine_entry : public QWidget
{
    Q_OBJECT

public:
    explicit Add_medicine_entry(QWidget *parent = nullptr);
    ~Add_medicine_entry();

private slots:

    void on_add_clicked();

private:
    Ui::Add_medicine_entry *ui;
};

#endif // ADD_MEDICINE_ENTRY_H

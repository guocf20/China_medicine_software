#ifndef DEL_MEDICINE_ENTRY_H
#define DEL_MEDICINE_ENTRY_H

#include <QDialog>

namespace Ui {
class Del_medicine_entry;
}

class Del_medicine_entry : public QDialog
{
    Q_OBJECT

public:
    explicit Del_medicine_entry(QWidget *parent = nullptr);
    ~Del_medicine_entry();

private slots:
    void on_submit_clicked();

private:
    Ui::Del_medicine_entry *ui;
};

#endif // DEL_MEDICINE_ENTRY_H

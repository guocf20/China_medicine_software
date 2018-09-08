#ifndef RECORD_FORM_H
#define RECORD_FORM_H

#include <QWidget>

namespace Ui {
class Record_Form;
}

class Record_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Record_Form(QWidget *parent = nullptr);
    void show_with_no_submit();
    ~Record_Form();

private slots:


    void on_pushButton_clicked();

private:
    Ui::Record_Form *ui;
};

#endif // RECORD_FORM_H

#ifndef SEARCH_FORM_H
#define SEARCH_FORM_H

#include <QWidget>

namespace Ui {
class search_Form;
}

class search_Form : public QWidget
{
    Q_OBJECT

public:
    explicit search_Form(QWidget *parent = nullptr);
    void set_pushButton_text(QString s);
    ~search_Form();

private slots:
    void on_pushButton_clicked();
private:
    Ui::search_Form *ui;
};

#endif // SEARCH_FORM_H

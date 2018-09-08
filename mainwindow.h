#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
   // void on_prescription_button_clicked();

   // void on_medicine_button_clicked();

   // void on_record_button_clicked();



    void on_action_search_record_triggered();

    void on_actionadd_record_triggered();

    void on_actiondel_record_triggered();

    void on_show_medicine_triggered();

    void on_add_medicine_triggered();

    void on_modify_medicine_triggered();

    void on_del_medicine_triggered();

    void on_actionversion_triggered();

    void on_actionauthor_triggered();

    void on_actionmodify_record_2_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

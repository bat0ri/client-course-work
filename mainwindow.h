#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_refresh_Det_clicked();

    void on_save_Det_clicked();

    void on_pushButton_Det_change_clicked();


    //void on_tabWidget_tabBarClicked(int index);

    void on_pushButton_Deliv_change_clicked();

    void on_pushButton_Reg_change_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_task_1_clicked();

    void on_task_2_buttom_clicked();



    void on_task_3_buttom_clicked();

    void on_proc_clicked();



    void on_radioButton_ORM_clicked();

    void on_radioButton_SQL_clicked();


private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *Det;
    QSqlTableModel *Deliv;
    QSqlTableModel *Register;
    int type_task;
};
#endif // MAINWINDOW_H

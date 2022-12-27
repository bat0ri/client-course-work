#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlRecord>
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QODBC");
    QString connectString = "DRIVER={SQL Server};";
    connectString.append("SERVER=DESKTOP-ING7ICB\\SQLEXPRESS;");   // Hostname,SQL-Server Instance
    connectString.append("DATABASE=secondDB;");  // Schema
    connectString.append("UID=DESKTOP-ING7ICB\\Нурсиль;");           // User
    connectString.append("PWD=;");           // Pass
    connectString.append("Trusted_Connection=Yes;");
    db.setDatabaseName(connectString);

    if(db.open()) {
        qDebug("NICE");
    } else {
        qDebug("LOOS");
    }

//    query = new QSqlQuery(db);
//    query->exec("SELECT * FROM Details");



}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}




void MainWindow::on_refresh_Det_clicked()
{
    Det->revertAll();
    Det->clear();
     ui->Details->clearFocus();
     ui->Details->setModel(Det);
     Det = new QSqlTableModel(this, db);
     Det->setEditStrategy(QSqlTableModel::OnManualSubmit);
     Det-> setTable("Details");
     Det->select();
     ui->Details->setModel(Det);

    Deliv->revertAll();
    Deliv->clear();
    ui->Deliv->clearFocus();
    ui->Deliv->setModel(Det);
    Deliv = new QSqlTableModel(this, db);
    Deliv->setEditStrategy(QSqlTableModel::OnManualSubmit);
    Deliv-> setTable("Delivery");
    Deliv->select();
    ui->Deliv->setModel(Deliv);

    Register->revertAll();
    Register->clear();
    ui->Register->clearFocus();
    ui->Register->setModel(Det);
    Register = new QSqlTableModel(this, db);
    Register->setEditStrategy(QSqlTableModel::OnManualSubmit);
    Register-> setTable("Register");
    Register->select();
    ui->Register->setModel(Register);
}


void MainWindow::on_save_Det_clicked()
{
    Det->submitAll();
    Det->clear();
     ui->Details->clearFocus();
     ui->Details->setModel(Det);
     Det = new QSqlTableModel(this, db);
     Det->setEditStrategy(QSqlTableModel::OnManualSubmit);
     Det-> setTable("Details");
     Det->select();
     ui->Details->setModel(Det);

     Deliv->submitAll();
     Deliv->clear();
     ui->Deliv->clearFocus();
     ui->Deliv->setModel(Det);
     Deliv = new QSqlTableModel(this, db);
     Deliv->setEditStrategy(QSqlTableModel::OnManualSubmit);
     Deliv-> setTable("Delivery");
     Deliv->select();
     ui->Deliv->setModel(Deliv);

     Register->submitAll();
     Register->clear();
     ui->Register->clearFocus();
     ui->Register->setModel(Det);
     Register = new QSqlTableModel(this, db);
     Register->setEditStrategy(QSqlTableModel::OnManualSubmit);
     Register-> setTable("Register");
     Register->select();
     ui->Register->setModel(Register);
}


void MainWindow::on_pushButton_Det_change_clicked()
{
    Det = new QSqlTableModel(this, db);
    Det->setEditStrategy(QSqlTableModel::OnManualSubmit);
    Det-> setTable("Details");
    Det->select();
    ui->dynamic_table->setModel(Det);
    ui->dynamic_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->label_2->setText("Details");
}


void MainWindow::on_pushButton_Deliv_change_clicked()
{
    Deliv = new QSqlTableModel(this, db);
    Deliv->setEditStrategy(QSqlTableModel::OnManualSubmit);
    Deliv-> setTable("Delivery");
    Deliv->select();
    ui->dynamic_table->setModel(Deliv);
    ui->label_2->setText("Delivery");

}


void MainWindow::on_pushButton_Reg_change_clicked()
{
    Register = new QSqlTableModel(this, db);
    Register->setEditStrategy(QSqlTableModel::OnManualSubmit);
    Register-> setTable("Register");
    Register->select();
    ui->dynamic_table->setModel(Register);
    ui->label_2->setText("Register");
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 0) {
        Det = new QSqlTableModel(this, db);
        Det->setEditStrategy(QSqlTableModel::OnManualSubmit);
        Det-> setTable("Details");
        Det->select();
        ui->Details->setModel(Det);

        Deliv = new QSqlTableModel(this, db);
        Deliv->setEditStrategy(QSqlTableModel::OnManualSubmit);
        Deliv-> setTable("Delivery");
        Deliv->select();
        ui->Deliv->setModel(Deliv);

        Register = new QSqlTableModel(this, db);
        Register->setEditStrategy(QSqlTableModel::OnManualSubmit);
        Register-> setTable("Register");
        Register->select();
        ui->Register->setModel(Register);
    } else if(index == 2) {
//        QSqlQuery query;
//           query.exec("Create view v as SELECT r.id_det, r.id_dogv,r.num_doc, r.id_sklad, r.register_qt, Det.qt,plan_qt, r.ed_izm, price FROM Register as r INNER JOIN Delivery as Del ON Del.id_det=r.id_det and Del.id_dogv=r.id_dogv INNER JOIN Details as Det ON Det.id_det=r.id_det and Det.id_sklad=r.id_sklad");

        QSqlQueryModel *setquery1 = new QSqlQueryModel;

        setquery1->setQuery("SELECT * FROM v");
        QTableView *tv = new QTableView(this);
        tv->setModel(setquery1);
        ui->view->setModel(setquery1);
    }
}


void MainWindow::on_task_1_clicked()
{
    short int year = ui->year->text().toShort();
    if(ui->year->text() != '\0') {
        if(ui->radio_task_1_SQL->isChecked() == true) {

            QSqlQueryModel *setquery1 = new QSqlQueryModel;
            QString sql = QString("SELECT r.id_sklad, r.num_doc, r.id_det, r.register_qt, r.date_deliv, d.plan_qt, d.last_deliv FROM Register as r INNER JOIN Delivery as d ON d.id_det = r.id_det and d.id_dogv = r.id_dogv WHERE d.last_deliv <'01/01/%1'").arg(year);
            setquery1->setQuery(sql);
            QTableView *tv = new QTableView(this);
            tv->setModel(setquery1);
            ui->table_task_1->setModel(setquery1);
        } else if(ui->radio_task_1_ORM->isChecked() == true) {

            QSqlTableModel *del = new QSqlTableModel(this, db);
            del->setEditStrategy(QSqlTableModel::OnManualSubmit);
            del-> setTable("Delivery");
            del->select();
            QSqlTableModel *reg = new QSqlTableModel(this, db);
            reg->setEditStrategy(QSqlTableModel::OnManualSubmit);
            reg-> setTable("Register");
            reg->select();
            QStandardItemModel *result = new QStandardItemModel(0, 7, this);
            result->setHeaderData(0, Qt::Horizontal, "id_sklad");
            result->setHeaderData(1, Qt::Horizontal, "num_doc");
            result->setHeaderData(2, Qt::Horizontal, "id_det");
            result->setHeaderData(3, Qt::Horizontal, "register_qt");
            result->setHeaderData(4, Qt::Horizontal, "date_deliv");
            result->setHeaderData(5, Qt::Horizontal, "plan_qt");
            result->setHeaderData(6, Qt::Horizontal, "last_deliv");
            QDate Date;
            Date.setDate((int)year, 1, 1);
            QModelIndex index;
            int index_x = 0;
            for(int i=0;i<reg->rowCount();i++){
                for(int j = 0; j<del->rowCount(); j++){
                    if(del->record(j).value("id_dogv").toInt() == reg->record(i).value("id_dogv").toInt()){
                        QDate deliv_dog = del->record(j).value("last_deliv").toDate();
                        if(deliv_dog < Date){
                            result->appendRow(NULL);
                            index = result->index(index_x, 6);
                            result->setData(index, del->record(j).value("last_deliv").toString());
                            index = result->index(index_x, 1);
                            result->setData(index, reg->record(i).value("num_doc").toString());
                            index = result->index(index_x, 0);
                            result->setData(index, reg->record(i).value("id_sklad").toString());
                            index = result->index(index_x, 2);
                            result->setData(index, reg->record(i).value("id_det").toString());
                            index = result->index(index_x, 3);
                            result->setData(index, reg->record(i).value("register_qt").toString());
                            index = result->index(index_x, 4);
                            result->setData(index, reg->record(i).value("date_deliv").toString());
                            index = result->index(index_x, 5);
                            result->setData(index, del->record(j).value("plan_qt").toString());
                            index_x++;
                        }
                    }
                }

            }
            ui->table_task_1->setModel(result);
        }
    }
}


void MainWindow::on_task_2_buttom_clicked()
{
    if(ui->year_2->text() != '\0') {

        short int year = ui->year_2->text().toShort();
        QSqlQueryModel *setquery1 = new QSqlQueryModel;
        QString sql = QString("SELECT DISTINCT d.id_dogv, d.id_det,last_deliv, d.plan_qt,RANK() OVER (ORDER BY d.last_deliv) as rank, SUM(register_qt) OVER (PARTITION BY d.id_det) as total FROM Delivery as d, Register as r WHERE d.id_dogv = r.id_dogv and d.last_deliv <'01/01/%1'").arg(year);
        setquery1->setQuery(sql);
        QTableView *tv = new QTableView(this);
        tv->setModel(setquery1);
        ui->window_func->setModel(setquery1);
    }
}


void MainWindow::on_task_3_buttom_clicked()
{
    short int plan = ui->plan_qt->text().toShort();
    short int qt = ui->reg_qt->text().toShort();

    if(type_task == 1){
        QSqlQueryModel *setquery1 = new QSqlQueryModel;
        QString sql = QString("SELECT id_det, id_sklad, last_op from Details as det WHERE EXISTS(select del.plan_qt from Delivery as del where del.plan_qt> %1 and del.id_det = det.id_det and NOT EXISTS(select r.register_qt from Register as r where r.register_qt <= %2  and del.id_dogv = r.id_dogv and r.id_det = det.id_det))").arg(plan).arg(qt);
        setquery1->setQuery(sql);
        QTableView *tv = new QTableView(this);
        tv->setModel(setquery1);
        ui->table_task_3->setModel(setquery1);
    } else if(type_task == 2){

        QSqlTableModel *det = new QSqlTableModel(this, db);
        det->setEditStrategy(QSqlTableModel::OnManualSubmit);
        det-> setTable("Details");
        det->select();

        QSqlTableModel *del = new QSqlTableModel(this, db);
        del->setEditStrategy(QSqlTableModel::OnManualSubmit);
        del-> setTable("Delivery");
        del->select();

        QSqlTableModel *reg = new QSqlTableModel(this, db);
        reg->setEditStrategy(QSqlTableModel::OnManualSubmit);
        reg-> setTable("Register");
        reg->select();

        QStandardItemModel *result = new QStandardItemModel(0, 3, this);
        result->setHeaderData(0, Qt::Horizontal, "id_det");
        result->setHeaderData(1, Qt::Horizontal, "id_sklad");
        result->setHeaderData(2, Qt::Horizontal, "last_op");


        QModelIndex index;
        int index_x = 0;
        bool b = true;
        for(int i = 0; i<det->rowCount(); i++){
            int id_det = det->record(i).value("id_det").toInt();

            for(int j = 0; j<del->rowCount();j++){
                int plan_qt = del->record(j).value("plan_qt").toInt();
                int dogv = del->record(j).value("id_dogv").toInt();
                if(plan_qt > plan && id_det == del->record(j).value("id_det").toInt()){
                    b = true;
                    for(int k = 0; k < reg->rowCount() && b==true; k++){
                        if(reg->record(k).value("id_dogv").toInt() == dogv && reg->record(k).value("id_det").toInt() == id_det){
                            if(reg->record(k).value("register_qt").toInt() <= qt){
                                b = false;
                            }
                        }
                    }
                    if(b == true){
                        result->appendRow(NULL);
                        index = result->index(index_x, 0);
                       result->setData(index, id_det);
                        index = result->index(index_x, 1);
                        result->setData(index, det->record(i).value("id_sklad").toInt());
                        index = result->index(index_x, 2);
                        result->setData(index, det->record(i).value("last_op").toString());
                        index_x++;
                    }

                }

            }

        }
        ui->table_task_3->setModel(result);
    }

}


void MainWindow::on_proc_clicked()
{
    short int id_sklad = ui->id_sklad->text().toShort();
    QSqlQuery query;
    QString sql = QString("DECLARE @a decimal(15,2) EXECUTE Get_price_sklad %1, @a out SELECT @a").arg(id_sklad);
    //setquery1->setQuery(sql);
    query.exec(sql);
    //QTableView *tv = new QTableView(this);
    //tv->setModel(setquery1);
    //ui->Details->setModel(setquery1);
    query.first();
    QString res = query.value(0).toString();
    ui->res_proc->setText(res);
}


void MainWindow::on_radioButton_ORM_clicked()
{
    type_task = 2;
}


void MainWindow::on_radioButton_SQL_clicked()
{
    type_task = 1;
}





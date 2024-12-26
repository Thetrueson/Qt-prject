#include "empupdate.h"
#include "ui_empupdate.h"

empUpdate::empUpdate(QSqlDatabase* db,QString id,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::empUpdate)
{
    ui->setupUi(this);
    this->db = db;
    this->id = id;
    setWindowFlags(Qt::FramelessWindowHint); // 禁用标题栏和边框
    QString sql = QString("select user_id from Employees where emp_id = '%1'").arg(id);
    QSqlQuery query;
    query.exec(sql);
    query.next();
    QString id1 = query.value(0).toString();
    sql = QString("select account from Users where user_id = '%1'").arg(id1);
    query.exec(sql);
    query.next();
    ui->accountLi->setText(query.value(0).toString());
    sql = QString("select emp_id,name,sex,title,salary,native,birthday,hire_date from Employees where emp_id = '%1'").arg(id);
    query.exec(sql);
    while(query.next())
    {
        QString data1 = query.value(0).toString();
        QString data2 = query.value(1).toString();
        QString data3 = query.value(2).toString();
        QString data4 = query.value(3).toString();
        QString data5 = query.value(4).toString();
        QString data6 = query.value(5).toString();
        QDate data7 = query.value(6).toDate();
        QDate data8 = query.value(7).toDate();
        ui->emp_idLi->setText(data1);
        ui->nameLi->setText(data2);
        ui->sexBox->setCurrentText(data3);
        ui->titleLi->setText(data4);
        ui->salaryLi->setText(data5);
        ui->nativeLi->setText(data6);
        ui->birthday->setDate(data7);
        ui->hire_date->setDate(data8);
    }
}

empUpdate::~empUpdate()
{
    delete ui;
}

void empUpdate::on_pushButton_2_clicked()
{
    this->hide();
}


void empUpdate::on_pushButton_clicked()
{
    QString data1 = ui->emp_idLi->text();
    QString data2 = ui->titleLi->text();
    QString data3 = ui->salaryLi->text();
    QString data4 = ui->nameLi->text();
    QString data5 = ui->sexBox->currentText();
    QString data6 = ui->nativeLi->text();
    QString data7 = ui->birthday->text();
    QString data8 = ui->hire_date->text();
    QString sql = QString("update Employees set title='%1',salary='%2',name='%3',sex='%4',native='%5',birthday='%6',hire_date='%7' where emp_id = '%8'")
                      .arg(data2).arg(data3).arg(data4).arg(data5).arg(data6).arg(data7).arg(data8).arg(data1);
    QSqlQuery query;
    if(query.exec(sql))
    {
        QMessageBox::information(this,"提示信息","更新成功");
        this->close();
        foreach (QWidget *widget, qApp->topLevelWidgets()) {
            if (widget->objectName() == "employee") {
                widget->close();
                break;
            }
        }
    }
    else
    {
        QMessageBox::warning(this,"提示信息","更新失败");
    }
}


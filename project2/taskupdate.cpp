#include "taskupdate.h"
#include "ui_taskupdate.h"

taskUpdate::taskUpdate(QSqlDatabase* db,QString id,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::taskUpdate)
{
    ui->setupUi(this);
    this->db = db;
    this->id = id;
    setWindowFlags(Qt::FramelessWindowHint); // 禁用标题栏和边框
    QString sql = QString("select name from Employees");
    QSqlQuery query;
    query.exec(sql);
    while(query.next())
    {
        ui->empbox->addItem(query.value(0).toString());
    }
    sql = QString("select task_id,task_name,execution_cycle,task_status,emp_id from Tasks where task_id = '%1'").arg(id);
    query.exec(sql);
    query.next();
    ui->task_idLi->setText(query.value(0).toString());
    ui->task_nameLi->setText(query.value(1).toString());
    ui->task_cycleLi->setText(query.value(2).toString());
    ui->statusBox->setCurrentText(query.value(3).toString());
    QString emp_id = query.value(4).toString();
    sql = QString("select name from Employees where emp_id = '%1'").arg(emp_id);
    query.exec(sql);
    query.next();
    ui->empbox->setCurrentText(query.value(0).toString());
}

taskUpdate::~taskUpdate()
{
    delete ui;
}

void taskUpdate::on_pushButton_2_clicked()
{
    this->hide();
}


void taskUpdate::on_pushButton_clicked()
{
    QString data1 = ui->task_idLi->text();
    QString data2 = ui->task_nameLi->text();
    QString data3 = ui->task_cycleLi->text();
    QString data4 = ui->statusBox->currentText();
    QString data5 = ui->empbox->currentText();
    QString sql = QString("select emp_id from Employees where name = '%1'").arg(data5);
    QSqlQuery query;
    query.exec(sql);
    query.next();
    data5 = query.value(0).toString();
    sql = QString("update Tasks set task_name = '%1',execution_cycle = '%2',task_status = '%3',emp_id = '%4' where task_id = '%5'")
              .arg(data2).arg(data3).arg(data4).arg(data5).arg(data1);
    if(query.exec(sql))
    {
        QMessageBox::information(this,"提示信息","更新成功");
        this->close();
        foreach (QWidget *widget, qApp->topLevelWidgets()) {
            if (widget->objectName() == "task") {
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


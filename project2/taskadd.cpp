#include "taskadd.h"
#include "ui_taskadd.h"

taskAdd::taskAdd(QSqlDatabase* db,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::taskAdd)
{
    ui->setupUi(this);
    this->db = db;
    setWindowFlags(Qt::FramelessWindowHint); // 禁用标题栏和边框
    QString sql = QString("select name from Employees");
    QSqlQuery query;
    query.exec(sql);
    while(query.next())
    {
        ui->empBox->addItem(query.value(0).toString());
    }
    ui->statusBox->addItem("待办");
    ui->statusBox->addItem("完成");
    ui->statusBox->addItem("放弃");
}

taskAdd::~taskAdd()
{
    delete ui;
}

void taskAdd::on_pushButton_2_clicked()
{
    this->hide();
}


void taskAdd::on_pushButton_clicked()
{
    QString data1 = ui->task_idLi->text();
    QString data2 = ui->task_nameLi->text();
    QString data3 = ui->empBox->currentText();
    QString data4 = ui->cycleLi->text();
    QString data5 = ui->statusBox->currentText();
    QString sql = QString("select emp_id from Employees where name = '%1'").arg(data3);
    QSqlQuery query;
    query.exec(sql);
    query.next();
    data3 = query.value(0).toString();
    sql = QString("insert into Tasks(task_id,task_name,emp_id,execution_cycle,task_status) values('%1','%2','%3','%4','%5')")
              .arg(data1).arg(data2).arg(data3).arg(data4).arg(data5);
    if(query.exec(sql))
    {
        QMessageBox::information(this,"提示信息","添加成功");
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
        QMessageBox::warning(this,"提示信息","添加失败");
    }
}


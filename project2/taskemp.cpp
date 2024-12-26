#include "taskemp.h"
#include "ui_taskemp.h"

taskEmp::taskEmp(QSqlDatabase* db,QString account,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::taskEmp)
{
    ui->setupUi(this);
    this->db = db;
    this->account = account;
    setWindowFlags(Qt::FramelessWindowHint); // 禁用标题栏和边框
    QString sql = QString("select user_id from Users where account = '%1'").arg(account);
    QSqlQuery query;
    query.exec(sql);
    query.next();
    QString user_id = query.value(0).toString();
    sql = QString("select emp_id from Employees where user_id = '%1'").arg(user_id);
    query.exec(sql);
    query.next();
    QString emp_id = query.value(0).toString();
    sql = QString("select task_id,task_name,execution_cycle,task_status from Tasks where emp_id = '%1'").arg(emp_id);
    query.exec(sql);
    int row = 0;
    while(query.next())
    {
        QString data1 = query.value(0).toString();
        QString data2 = query.value(1).toString();
        QString data3 = query.value(2).toString();
        QString data4 = query.value(3).toString();


        ui->taskList->insertRow(row);
        ui->taskList->setItem(row, 0, new QTableWidgetItem(data1));
        ui->taskList->setItem(row, 1, new QTableWidgetItem(data2));
        ui->taskList->setItem(row, 2, new QTableWidgetItem(data3));
        ui->taskList->setItem(row, 3, new QTableWidgetItem(data4));

        if(data4=="待办")
        {
            // 添加按钮到最后一列
            QWidget *buttonsWidget = new QWidget();
            QPushButton *editButton = new QPushButton("完成");
            QPushButton *deleteButton = new QPushButton("放弃");

            QHBoxLayout *layout = new QHBoxLayout(buttonsWidget);
            layout->addWidget(editButton);
            layout->addWidget(deleteButton);
            layout->setAlignment(Qt::AlignCenter);
            layout->setContentsMargins(0, 0, 0, 0);

            buttonsWidget->setLayout(layout);
            ui->taskList->setCellWidget(row, 4, buttonsWidget);

            connect(editButton, &QPushButton::clicked, this, &taskEmp::onEditButtonClicked);
            connect(deleteButton, &QPushButton::clicked, this, &taskEmp::onDeleteButtonClicked);
        }


        row++;

    }
}

taskEmp::~taskEmp()
{
    delete ui;
}

void taskEmp::on_pushButton_clicked()
{
    this->hide();
}

void taskEmp::onEditButtonClicked()
{
    // 获取点击的按钮
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    // 获取按钮所在的QWidget
    QWidget *widget = button->parentWidget();
    if (!widget) return;

    // 获取单元格的行号
    int row = ui->taskList->indexAt(widget->pos()).row();

    // 获取整行的信息
    if (row >= 0) {
        QTableWidgetItem *item = ui->taskList->item(row, 0); // 获取第一列的数据
        if (item)
        {
            QString sql = QString("update Tasks set task_status = '完成' where task_id = '%1'").arg(item->text());
            QSqlQuery query;
            if(query.exec(sql))
            {
                QMessageBox::information(this,"提示信息","任务完成成功");
                taskEmp::on_pushButton_2_clicked();
            }
            else
            {
                QMessageBox::warning(this,"提示信息","任务完成失败");
            }
        }
    }
}

void taskEmp::onDeleteButtonClicked()
{
    // 获取点击的按钮
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    // 获取按钮所在的QWidget
    QWidget *widget = button->parentWidget();
    if (!widget) return;

    // 获取单元格的行号
    int row = ui->taskList->indexAt(widget->pos()).row();

    // 获取整行的信息
    if (row >= 0) {
        QTableWidgetItem *item = ui->taskList->item(row, 0); // 获取第一列的数据
        if (item)
        {
            QString sql = QString("update Tasks set task_status = '放弃' where task_id = '%1'").arg(item->text());
            QSqlQuery query;
            if(query.exec(sql))
            {
                QMessageBox::information(this,"提示信息","任务放弃成功");
                taskEmp::on_pushButton_2_clicked();
            }
            else
            {
                QMessageBox::warning(this,"提示信息","任务放弃失败");
            }
        }
    }
}

void taskEmp::on_pushButton_2_clicked()
{
    QString data = ui->taskNameLi->text();
    QString sql = QString("select user_id from Users where account = '%1'").arg(account);
    QSqlQuery query;
    query.exec(sql);
    query.next();
    QString user_id = query.value(0).toString();
    sql = QString("select emp_id from Employees where user_id = '%1'").arg(user_id);
    query.exec(sql);
    query.next();
    QString emp_id = query.value(0).toString();
    sql = QString("select task_id,task_name,execution_cycle,task_status from Tasks where task_name like '%%1%' and emp_id = '%2'")
                      .arg(data).arg(emp_id);
    query.exec(sql);
    int row = 0;
    ui->taskList->setRowCount(0);
    while(query.next())
    {
        QString data1 = query.value(0).toString();
        QString data2 = query.value(1).toString();
        QString data3 = query.value(2).toString();
        QString data4 = query.value(3).toString();


        ui->taskList->insertRow(row);
        ui->taskList->setItem(row, 0, new QTableWidgetItem(data1));
        ui->taskList->setItem(row, 1, new QTableWidgetItem(data2));
        ui->taskList->setItem(row, 2, new QTableWidgetItem(data3));
        ui->taskList->setItem(row, 3, new QTableWidgetItem(data4));

        if(data4=="待办")
        {
            // 添加按钮到最后一列
            QWidget *buttonsWidget = new QWidget();
            QPushButton *editButton = new QPushButton("完成");
            QPushButton *deleteButton = new QPushButton("放弃");

            QHBoxLayout *layout = new QHBoxLayout(buttonsWidget);
            layout->addWidget(editButton);
            layout->addWidget(deleteButton);
            layout->setAlignment(Qt::AlignCenter);
            layout->setContentsMargins(0, 0, 0, 0);

            buttonsWidget->setLayout(layout);
            ui->taskList->setCellWidget(row, 4, buttonsWidget);

            connect(editButton, &QPushButton::clicked, this, &taskEmp::onEditButtonClicked);
            connect(deleteButton, &QPushButton::clicked, this, &taskEmp::onDeleteButtonClicked);
        }


        row++;

    }
}


#include "task.h"
#include "ui_task.h"

task::task(QSqlDatabase* db,QString account,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::task)
{
    ui->setupUi(this);
    this->db = db;
    this->account = account;
    setWindowFlags(Qt::FramelessWindowHint); // 禁用标题栏和边框
    this->setObjectName("task");
    QString sql = QString("select task_id,task_name,execution_cycle,task_status,emp_id from Tasks");
    QSqlQuery query;
    query.exec(sql);
    int row = 0;
    while(query.next())
    {
        QString data1 = query.value(0).toString();
        QString data2 = query.value(1).toString();
        QString data3 = query.value(2).toString();
        QString data4 = query.value(3).toString();
        QString data5 = query.value(4).toString();

        QString sql = QString("select name from Employees where emp_id = '%1'").arg(data5);
        QSqlQuery query;
        query.exec(sql);
        query.next();
        data5 = query.value(0).toString();

        ui->taskList->insertRow(row);
        ui->taskList->setItem(row, 0, new QTableWidgetItem(data1));
        ui->taskList->setItem(row, 1, new QTableWidgetItem(data2));
        ui->taskList->setItem(row, 2, new QTableWidgetItem(data3));
        ui->taskList->setItem(row, 3, new QTableWidgetItem(data4));
        ui->taskList->setItem(row, 4, new QTableWidgetItem(data5));

        // 添加按钮到最后一列
        QWidget *buttonsWidget = new QWidget();
        QPushButton *editButton = new QPushButton("修改");
        QPushButton *deleteButton = new QPushButton("删除");

        QHBoxLayout *layout = new QHBoxLayout(buttonsWidget);
        layout->addWidget(editButton);
        layout->addWidget(deleteButton);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(0, 0, 0, 0);

        buttonsWidget->setLayout(layout);
        ui->taskList->setCellWidget(row, 5, buttonsWidget);

        connect(editButton, &QPushButton::clicked, this, &task::onEditButtonClicked);
        connect(deleteButton, &QPushButton::clicked, this, &task::onDeleteButtonClicked);


        row++;

    }
}

task::~task()
{
    delete ui;
}

void task::on_pushButton_clicked()
{
    this->hide();
}


void task::onEditButtonClicked()
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
            QString sql = QString("select task_id,task_name,execution_cycle,task_status from Tasks where task_id = '%1'").arg(item->text());
            QSqlQuery query;
            if(query.exec(sql))
            {
                taskUpdate* t = new taskUpdate(this->db,item->text());
                t->show();
            }
        }
    }
}

void task::onDeleteButtonClicked()
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
            QString sql = QString("delete from Tasks where task_id = '%1'").arg(item->text());
            QSqlQuery query;
            if(query.exec(sql))
            {
                QMessageBox::information(this,"提示信息","任务删除成功");
                task::on_pushButton_2_clicked();
            }
            else
            {
                QMessageBox::warning(this,"提示信息","任务删除失败");
            }
        }
    }
}


void task::on_pushButton_2_clicked()
{
    ui->taskList->setRowCount(0);
    QSqlQuery query;
    QString sql;
    if(ui->choiceBox->currentText()=="任务名")
    {
        sql = QString("select task_id,task_name,execution_cycle,task_status,emp_id from Tasks where task_name like '%%1%'")
                          .arg(ui->nameLi->text());
    }
    else
    {
        sql = QString("select task_id,task_name,execution_cycle,task_status,emp_id from Tasks where emp_id in (select emp_id from Employees where name like '%%1%')")
                  .arg(ui->nameLi->text());
    }
    query.exec(sql);
    int row = 0;
    while(query.next())
    {
        QString data1 = query.value(0).toString();
        QString data2 = query.value(1).toString();
        QString data3 = query.value(2).toString();
        QString data4 = query.value(3).toString();
        QString data5 = query.value(4).toString();

        QString sql = QString("select name from Employees where emp_id = '%1'").arg(data5);
        QSqlQuery query;
        query.exec(sql);
        query.next();
        data5 = query.value(0).toString();

        ui->taskList->insertRow(row);
        ui->taskList->setItem(row, 0, new QTableWidgetItem(data1));
        ui->taskList->setItem(row, 1, new QTableWidgetItem(data2));
        ui->taskList->setItem(row, 2, new QTableWidgetItem(data3));
        ui->taskList->setItem(row, 3, new QTableWidgetItem(data4));
        ui->taskList->setItem(row, 4, new QTableWidgetItem(data5));

        // 添加按钮到最后一列
        QWidget *buttonsWidget = new QWidget();
        QPushButton *editButton = new QPushButton("修改");
        QPushButton *deleteButton = new QPushButton("删除");

        QHBoxLayout *layout = new QHBoxLayout(buttonsWidget);
        layout->addWidget(editButton);
        layout->addWidget(deleteButton);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(0, 0, 0, 0);

        buttonsWidget->setLayout(layout);
        ui->taskList->setCellWidget(row, 5, buttonsWidget);

        connect(editButton, &QPushButton::clicked, this, &task::onEditButtonClicked);
        connect(deleteButton, &QPushButton::clicked, this, &task::onDeleteButtonClicked);


        row++;

    }
}


void task::on_pushButton_3_clicked()
{
    taskAdd* t = new taskAdd(this->db);
    t->show();
}


#include "employee.h"
#include "ui_employee.h"

employee::employee(QSqlDatabase* db,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::employee)
{
    ui->setupUi(this);
    this->db = db;
    this->setObjectName("employee");
    setWindowFlags(Qt::FramelessWindowHint); // 禁用标题栏和边框
    QString sql = QString("select emp_id,name,title,salary from Employees");
    QSqlQuery query;
    query.exec(sql);
    int row = 0;
    while(query.next())
    {
        QString data1 = query.value(0).toString();
        QString data2 = query.value(1).toString();
        QString data3 = query.value(2).toString();
        QString data4 = query.value(3).toString();


        ui->employeeList->insertRow(row);
        ui->employeeList->setItem(row, 0, new QTableWidgetItem(data1));
        ui->employeeList->setItem(row, 1, new QTableWidgetItem(data2));
        ui->employeeList->setItem(row, 2, new QTableWidgetItem(data3));
        ui->employeeList->setItem(row, 3, new QTableWidgetItem(data4));


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
        ui->employeeList->setCellWidget(row, 4, buttonsWidget);

        connect(editButton, &QPushButton::clicked, this, &employee::onEditButtonClicked);
        connect(deleteButton, &QPushButton::clicked, this, &employee::onDeleteButtonClicked);

        row++;

    }
}

employee::~employee()
{
    delete ui;
}

void employee::on_pushButton_3_clicked()
{
    this->hide();
}


void employee::on_pushButton_2_clicked()
{
    QString name = ui->searchLi->text();
    QString sql = QString("select emp_id,name,title,salary from Employees where name like '%%1%'").arg(name);
    QSqlQuery query;
    query.exec(sql);
    ui->employeeList->setRowCount(0);
    int row = 0;
    while(query.next())
    {
        QString data1 = query.value(0).toString();
        QString data2 = query.value(1).toString();
        QString data3 = query.value(2).toString();
        QString data4 = query.value(3).toString();


        ui->employeeList->insertRow(row);
        ui->employeeList->setItem(row, 0, new QTableWidgetItem(data1));
        ui->employeeList->setItem(row, 1, new QTableWidgetItem(data2));
        ui->employeeList->setItem(row, 2, new QTableWidgetItem(data3));
        ui->employeeList->setItem(row, 3, new QTableWidgetItem(data4));


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
        ui->employeeList->setCellWidget(row, 4, buttonsWidget);

        connect(editButton, &QPushButton::clicked, this, &employee::onEditButtonClicked);
        connect(deleteButton, &QPushButton::clicked, this, &employee::onDeleteButtonClicked);

        row++;

    }
}

void employee::onEditButtonClicked()
{
    // 编辑按钮点击后的处理逻辑
    // 获取点击的按钮
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    // 获取按钮所在的QWidget
    QWidget *widget = button->parentWidget();
    if (!widget) return;

    // 获取单元格的行号
    int row = ui->employeeList->indexAt(widget->pos()).row();

    QString id;

    // 获取整行的信息
    if (row >= 0) {
        QTableWidgetItem *item = ui->employeeList->item(row, 0); // 获取第一列的数据
        if (item)
        {
            id = item->text();
        }
    }
    empUpdate* e = new empUpdate(this->db,id);
    e->show();
}

void employee::onDeleteButtonClicked()
{
    // 删除按钮点击后的处理逻辑
    // 获取点击的按钮
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    // 获取按钮所在的QWidget
    QWidget *widget = button->parentWidget();
    if (!widget) return;

    // 获取单元格的行号
    int row = ui->employeeList->indexAt(widget->pos()).row();

    // 获取整行的信息
    if (row >= 0) {
        QTableWidgetItem *item = ui->employeeList->item(row, 0); // 获取第一列的数据
        if (item) {
            QString id = item->text();
            // QString sql = QString("select user_id from Employees where emp_id = '%1'").arg(id);
            QSqlQuery query;
            // query.exec(sql);
            // query.next();
            // QString id1 = query.value(0).toString();
            QString sql = QString("delete from Employees where emp_id = '%1'").arg(id);
            // qDebug()<<sql;
            // query.exec(sql);
            // sql = QString("delete from Users where user_id = '%1'").arg(id1);
            // qDebug()<<sql;
            if(query.exec(sql))
            {
                QMessageBox::information(this,"提示信息","删除成功");
            }
            else
            {
                QMessageBox::warning(this,"提示信息","删除失败");
            }
        }
    }
    QString sql = QString("select emp_id,name,title,salary from Employees");
    QSqlQuery query;
    ui->employeeList->setRowCount(0);
    query.exec(sql);
    row = 0;
    while(query.next())
    {
        QString data1 = query.value(0).toString();
        QString data2 = query.value(1).toString();
        QString data3 = query.value(2).toString();
        QString data4 = query.value(3).toString();


        ui->employeeList->insertRow(row);
        ui->employeeList->setItem(row, 0, new QTableWidgetItem(data1));
        ui->employeeList->setItem(row, 1, new QTableWidgetItem(data2));
        ui->employeeList->setItem(row, 2, new QTableWidgetItem(data3));
        ui->employeeList->setItem(row, 3, new QTableWidgetItem(data4));


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
        ui->employeeList->setCellWidget(row, 4, buttonsWidget);

        connect(editButton, &QPushButton::clicked, this, &employee::onEditButtonClicked);
        connect(deleteButton, &QPushButton::clicked, this, &employee::onDeleteButtonClicked);

        row++;

    }
}


void employee::on_pushButton_clicked()
{
    empAdd* e = new empAdd(this->db);
    e->show();
}


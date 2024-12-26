#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <empupdate.h>
#include <empadd.h>

namespace Ui {
class employee;
}

class employee : public QWidget
{
    Q_OBJECT

public:
    explicit employee(QSqlDatabase* db,QWidget *parent = nullptr);
    ~employee();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void onEditButtonClicked();  // 编辑按钮的槽函数
    void onDeleteButtonClicked();  // 删除按钮的槽函数

    void on_pushButton_clicked();

private:
    Ui::employee *ui;
    QSqlDatabase* db;
};

#endif // EMPLOYEE_H

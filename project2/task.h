#ifndef TASK_H
#define TASK_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QApplication>
#include <QMessageBox>
#include <taskupdate.h>
#include <map>
#include<taskadd.h>

namespace Ui {
class task;
}

class task : public QWidget
{
    Q_OBJECT

public:
    explicit task(QSqlDatabase* db,QString account,QWidget *parent = nullptr);
    ~task();

private slots:
    void on_pushButton_clicked();
    void onEditButtonClicked();  // 编辑按钮的槽函数
    void onDeleteButtonClicked();  // 删除按钮的槽函数


    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::task *ui;
    QSqlDatabase* db;
    QString account;
};

#endif // TASK_H

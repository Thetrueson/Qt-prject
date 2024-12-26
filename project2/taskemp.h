#ifndef TASKEMP_H
#define TASKEMP_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QApplication>
#include <QMessageBox>

namespace Ui {
class taskEmp;
}

class taskEmp : public QWidget
{
    Q_OBJECT

public:
    explicit taskEmp(QSqlDatabase* db,QString account,QWidget *parent = nullptr);
    ~taskEmp();

private slots:
    void on_pushButton_clicked();

    void onEditButtonClicked();  // 编辑按钮的槽函数
    void onDeleteButtonClicked();  // 删除按钮的槽函数

    void on_pushButton_2_clicked();

private:
    Ui::taskEmp *ui;
    QSqlDatabase* db;
    QString account;
};

#endif // TASKEMP_H

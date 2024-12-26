#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QApplication>
#include <QMessageBox>
#include "employee.h"
#include <userupdate.h>
#include <task.h>
#include <taskemp.h>

namespace Ui {
class menu;
}

class menu : public QWidget
{
    Q_OBJECT

public:
    explicit menu(QSqlDatabase *db ,QString account ,QWidget *parent = nullptr);
    ~menu();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::menu *ui;
    QSqlDatabase *db;
    QString account;
};

#endif // MENU_H

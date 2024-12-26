#ifndef TASKADD_H
#define TASKADD_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class taskAdd;
}

class taskAdd : public QWidget
{
    Q_OBJECT

public:
    explicit taskAdd(QSqlDatabase* db,QWidget *parent = nullptr);
    ~taskAdd();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::taskAdd *ui;
    QSqlDatabase* db;
};

#endif // TASKADD_H

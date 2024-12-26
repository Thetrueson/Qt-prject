#ifndef EMPADD_H
#define EMPADD_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QCryptographicHash>

namespace Ui {
class empAdd;
}

class empAdd : public QWidget
{
    Q_OBJECT

public:
    explicit empAdd(QSqlDatabase* db,QWidget *parent = nullptr);
    ~empAdd();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::empAdd *ui;
    QSqlDatabase* db;
};

#endif // EMPADD_H

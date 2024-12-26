#ifndef USERUPDATE_H
#define USERUPDATE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QCryptographicHash>

namespace Ui {
class userUpdate;
}

class userUpdate : public QWidget
{
    Q_OBJECT

public:
    explicit userUpdate(QSqlDatabase* db,QString account,QWidget *parent = nullptr);
    ~userUpdate();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::userUpdate *ui;
    QSqlDatabase* db;
    QString account;
};

#endif // USERUPDATE_H

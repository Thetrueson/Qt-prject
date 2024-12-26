#ifndef TASKUPDATE_H
#define TASKUPDATE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class taskUpdate;
}

class taskUpdate : public QWidget
{
    Q_OBJECT

public:
    explicit taskUpdate(QSqlDatabase* db,QString id,QWidget *parent = nullptr);
    ~taskUpdate();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::taskUpdate *ui;
    QSqlDatabase* db;
    QString id;
};

#endif // TASKUPDATE_H

#ifndef EMPUPDATE_H
#define EMPUPDATE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QWindow>
#include <QPainter>
#include <QWidget>

namespace Ui {
class empUpdate;
}

class empUpdate : public QWidget
{
    Q_OBJECT

public:
    explicit empUpdate(QSqlDatabase* db,QString id,QWidget *parent = nullptr);
    ~empUpdate();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::empUpdate *ui;
    QSqlDatabase* db;
    QString id;
};

#endif // EMPUPDATE_H

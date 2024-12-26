#include "empadd.h"
#include "ui_empadd.h"

empAdd::empAdd(QSqlDatabase* db,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::empAdd)
{
    ui->setupUi(this);
    this->db = db;
    setWindowFlags(Qt::FramelessWindowHint); // 禁用标题栏和边框
}

empAdd::~empAdd()
{
    delete ui;
}

void empAdd::on_pushButton_2_clicked()
{
    this->hide();
}


void empAdd::on_pushButton_clicked()
{
    QString data1 = ui->emp_idLi->text();
    QString data2 = ui->nameLi->text();
    QString data3 = ui->sexBo->currentText();
    QString data4 = ui->titleLi->text();
    QString data5 = ui->salaryLi->text();
    QString data6 = ui->user_idLi->text();
    QString data7 = ui->accountLi->text();
    QString data8 = ui->passwordLi->text();
    QString data9 = ui->birthday->text();
    QString data10 = ui->nativeLi->text();
    QString data11 = ui->hire_date->text();

    //Md5加密
    QString originalText = data8;
    QByteArray data = originalText.toUtf8();
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(data);
    QByteArray md5Hash = hash.result();
    QString md5HashString = md5Hash.toHex().constData();

    QString sql = QString("insert into Users(user_id,account,password) values('%1','%2','%3')").arg(data6).arg(data7).arg(md5HashString);
    QSqlQuery query;
    query.exec(sql);
    sql = QString("insert into Employees(emp_id,name,sex,title,birthday,salary,native,user_id,hire_date) values('%1','%2','%3','%4','%5','%6','%7','%8','%9')")
              .arg(data1).arg(data2).arg(data3).arg(data4).arg(data9).arg(data5).arg(data10).arg(data6).arg(data11);
    if(query.exec(sql))
    {
        QMessageBox::information(this,"提示信息","添加成功");
        this->close();
        foreach (QWidget *widget, qApp->topLevelWidgets()) {
            if (widget->objectName() == "employee") {
                widget->close();
                break;
            }
        }
    }
    else
    {
        QMessageBox::warning(this,"提示信息","添加失败");
    }
}


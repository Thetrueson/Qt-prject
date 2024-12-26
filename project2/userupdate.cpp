#include "userupdate.h"
#include "ui_userupdate.h"

userUpdate::userUpdate(QSqlDatabase* db,QString account,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::userUpdate)
{
    ui->setupUi(this);
    this->db = db;
    this->account = account;
    ui->accountLi->setText(account);
    if(account == "admin")
    {
        ui->accountLi->setReadOnly(true);
    }
    setWindowFlags(Qt::FramelessWindowHint); // 禁用标题栏和边框
}

userUpdate::~userUpdate()
{
    delete ui;
}

void userUpdate::on_pushButton_2_clicked()
{
    this->hide();
}


void userUpdate::on_pushButton_clicked()
{
    QString data1 = ui->accountLi->text();
    QString data2 = ui->old_passwordLi->text();
    QString data3 = ui->new_passwordLi->text();
    QString data4 = ui->renew_passwordLi->text();

    //Md5加密
    QString originalText = data2;
    QByteArray data = originalText.toUtf8();
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(data);
    QByteArray md5Hash = hash.result();
    QString md5HashString = md5Hash.toHex().constData();

    QString sql = QString("select password from Users where account = '%1'").arg(data1);
    QSqlQuery query;
    if(query.exec(sql)&&query.next()&&query.value(0).toString()!=md5HashString)
    {
        QMessageBox::warning(this,"提示信息","旧密码输入错误");
    }
    else if(data3!=data4)
    {
        QMessageBox::warning(this,"提示信息","新密码输入不一致");
    }
    else{
        QString originalText = data3;
        QByteArray data = originalText.toUtf8();
        QCryptographicHash hash(QCryptographicHash::Md5);
        hash.addData(data);
        QByteArray md5Hash = hash.result();
        QString md5HashString = md5Hash.toHex().constData();
        sql = QString("update Users set account='%1',password='%2' where account = '%3'").arg(data1).arg(md5HashString).arg(account);
        if(query.exec(sql))
        {
            QMessageBox::information(this,"提示信息","修改成功");
            this->close();
            foreach (QWidget *widget, qApp->topLevelWidgets()) {
                if (widget->objectName() == "widget") {
                    widget->show();
                }
                if (widget->objectName() == "menu") {
                    widget->close();
                }
            }
        }
        else
        {
            QMessageBox::warning(this,"提示信息","修改失败");
        }
    }
}


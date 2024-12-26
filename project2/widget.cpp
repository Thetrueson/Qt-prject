#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setObjectName("widget");
    this->setWindowTitle("登陆");

    //连接数据库
    db = QSqlDatabase::addDatabase("QODBC");    //加载数据库驱动
    db.setPort(1433);
    db.setDatabaseName("Driver={SQL Server};Server=LENOVO;Database=hotel;Uid=test;Pwd=hzs520..;");
    if(db.open())
    {
        QMessageBox::information(this,"连接提示","连接成功");
    }
    else
    {
        QMessageBox::warning(this,"连接提示","连接失败");
        QApplication::quit();
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_loginBt_clicked()
{
    QString account = ui->accountLi->text();
    QString password = ui->passwordLi->text();

    //Md5加密
    QString originalText = password;
    QByteArray data = originalText.toUtf8();
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(data);
    QByteArray md5Hash = hash.result();
    QString md5HashString = md5Hash.toHex().constData();

    //登录判断
    QString sql = QString("select password from Users where '%1'=account;").arg(account);
    QSqlQuery query;
    if(query.exec(sql)&&query.next()&&query.value(0).toString()==md5HashString)
    {
        QMessageBox::information(this,"登陆提示","登录成功");

        //打开管理主页
        this->close();
        menu *m = new menu(&db,account);
        m->show();
    }
    else
    {
        QMessageBox::warning(this,"登录提示","登录失败");
    }
}


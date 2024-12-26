#include "menu.h"
#include "ui_menu.h"

menu::menu(QSqlDatabase *db ,QString account ,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::menu)
{
    ui->setupUi(this);
    this->db = db;
    this->account = account;
    this->setObjectName("menu");
    ui->manageLa->setText("你好,"+account);
    QFont font;
    font.setPointSize(12);
    ui->manageLa->setFont(font);
    this->setWindowTitle("主页");
    //setWindowFlags(Qt::FramelessWindowHint); // 禁用标题栏和边框
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_4_clicked()
{
    QApplication::quit();
}


void menu::on_pushButton_clicked()
{
    if(account == "admin")
    {
        employee* e = new employee(this->db);
        e->show();
    }
    else
    {
        QMessageBox::warning(this,"提示信息","没有权限访问");
    }
}


void menu::on_pushButton_3_clicked()
{
    userUpdate* u = new userUpdate(this->db,account);
    u->show();
}


void menu::on_pushButton_2_clicked()
{
    if(account == "admin")
    {
        task* t = new task(this->db,this->account);
        t->show();
    }
    else
    {
        taskEmp* t = new taskEmp(this->db,this->account);
        t->show();
    }
}


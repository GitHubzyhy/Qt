#include "page_login.h"
#include "ui_page_login.h"
#include<QMovie>
#include<QPainter>
#include<QMessageBox>
Page_Login::Page_Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page_Login)
    ,m_ptrStuSql(nullptr)
{
    ui->setupUi(this);
    auto movie=new QMovie(":/login_load.gif");
    ui->lb_gif->setMovie(movie);
    QSize si(388,81);
    movie->setScaledSize(si);
    movie->start();

    m_ptrStuSql=stuSql::getinstance();

}

Page_Login::~Page_Login()
{
    delete ui;
}



void Page_Login::on_bt_login_clicked()
{
    UserInfo info;
    //从ui界面获取用户名和密码
    info.username=ui->le_user->text();//获取搜索框的内容
    info.password=ui->le_password->text();
    if(info.username.isEmpty())
    {
        QMessageBox::information(nullptr,"警告","没有填写用户名");
        return;
    }
    if(info.password.isEmpty())
    {
        QMessageBox::information(nullptr,"警告","没有填写密码");
        return;
    }
    //数据库查找用户名和密码

    QList<UserInfo> lUser=m_ptrStuSql->getAllUser();

    bool change=false;
    for(int i=0;i<lUser.size();++i)
    {
        change=false;
        if(lUser[i].username==info.username && lUser[i].password==info.password)
        {
            change=true;
            break;
        }
    }
    if(change)
    {
        //成功就进入主界面
        emit SendLoginSuccess();//发出信号
    }
    else
    {
        QMessageBox::information(nullptr,"警告","身份验证失败");
    }

}


void Page_Login::on_bt_exe_clicked()
{
    exit(0);//退出整个程序
}


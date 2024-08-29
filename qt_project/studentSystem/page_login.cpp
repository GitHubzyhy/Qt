#include "page_login.h"
#include "ui_page_login.h"
#include <QMovie>
#include <QMessageBox>

Page_Login::Page_Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page_Login)
    , m_ptrStuSql(nullptr)
{
    ui->setupUi(this);

    auto movie = new QMovie(":/login_load.gif");
    ui->lb_gif->setMovie(movie);
    QSize si(388, 81);
    movie->setScaledSize(si);
    movie->start();

    m_ptrStuSql = stuSql::getinstance();//实例了一个静态变量
}

Page_Login::~Page_Login()
{
    delete ui;
}
//确认登录按钮
void Page_Login::on_btnLogin_clicked()
{
    UserInfo info;
    //从ui界面获取用户名和密码
    info.username = ui->lineUser->text(); //获取搜索框的内容
    info.password = ui->linePassword->text();
    if (info.username.isEmpty())
    {
        QMessageBox::information(nullptr, "警告", "没有填写用户名");
        return;
    }

    //数据库查找用户名和密码
    QList<UserInfo> lUser = m_ptrStuSql->getAllUser();

    bool change = false;
    for (int i = 0; i < lUser.size(); ++i)
    {
        change = false;
        if (lUser[i].username == info.username && lUser[i].password == info.password)
        {
            change = true;
            break;
        }
    }
    if (change)//成功就进入主界面
        emit SendLoginSuccess();//发出信号
    else
        QMessageBox::information(nullptr, "警告", "身份验证失败");
}
//用户名编辑完成
void Page_Login::on_lineUser_editingFinished()
{
    QString userName = ui->lineUser->text();
    if (!m_ptrStuSql->isExit(userName))
    {
        QMessageBox::critical(this, "错误", tr("用户：%1 不存在！").arg(userName));
        ui->lineUser->clear();
    }
    else
        qDebug() << "用户: " << userName << "存在!";
}

#ifndef PAGE_LOGIN_H
#define PAGE_LOGIN_H

#include <QWidget>
#include<stusql.h>

namespace Ui
{
    class Page_Login;
}

class Page_Login : public QWidget
{
    Q_OBJECT

public:
    explicit Page_Login(QWidget *parent = nullptr);
    ~Page_Login();

private slots://槽函数
    void on_btnLogin_clicked();//确认登录按钮

    void on_lineUser_editingFinished();//用户名编辑完成

signals://信号
    void SendLoginSuccess();//发出信号

private:
    Ui::Page_Login *ui;

    stuSql *m_ptrStuSql;//数据库操作
};

#endif // PAGE_LOGIN_H

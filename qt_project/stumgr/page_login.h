#ifndef PAGE_LOGIN_H
#define PAGE_LOGIN_H

#include <QWidget>
#include<stusql.h>
namespace Ui {
class Page_Login;
}

class Page_Login : public QWidget
{
    Q_OBJECT

public:
    explicit Page_Login(QWidget *parent = nullptr);
    ~Page_Login();

private slots://槽函数
    void on_bt_login_clicked();

    void on_bt_exe_clicked();

signals://信号
    void SendLoginSuccess();//发出信号
private:
    Ui::Page_Login *ui;
   stuSql *m_ptrStuSql;//指向学生表的指针
};

#endif // PAGE_LOGIN_H

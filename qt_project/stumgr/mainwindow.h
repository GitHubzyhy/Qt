#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"page_login.h"
#include"stusql.h"
#include<dlg_addstu.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void keyPressEvent(QKeyEvent *event) override;//重写虚函数使按键盘刷新的功能
    void initNames();//初始化测试信息的姓名
    void changeTheme();//切换主题
    void dataFlush();//刷新数据
private slots:
    void on_btn_simulation_clicked();

    void on_btn_add_clicked();


    void on_btn_clear_clicked();
    void on_btn_del_clicked();


    void on_btn_update_clicked();

    void on_btn_search_clicked();

    void on_exe_clicked();


private:
    Ui::MainWindow *ui;
    Page_Login m_dlgLogin;//登录界面的对象
    stuSql *m_ptrStuSql;
    QStringList m_lNames;//测试信息的名字集合

    Dlg_AddStu m_dlgAddStu;//添加界面对象

};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "page_login.h"//登录
#include "stusql.h"//数据库
#include <dlg_addstu.h>//添加更新自定义对话框

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class QTreeWidgetItem;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initNames();//将文件中的名字读取到m_lNames
    void changeTheme();//切换主题
    void dataFlush();//刷新数据

private slots:
    void on_btn_simulation_clicked();//随机模拟数据

    void on_btn_add_clicked();//添加
    void on_btn_clear_clicked();//清空
    void on_btn_del_clicked();//删除
    void on_btn_update_clicked();//更新
    void on_btn_search_clicked();//搜索

    //根据QTreeWidget条目变化切换QStackWidget的页面
    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current,
                                          QTreeWidgetItem *previous);

    void on_checkBox_toggled(bool checked);//复选框判断是否全选

private:
    Ui::MainWindow *ui;

    QStringList m_lNames;//测试信息的名字集合
    Page_Login m_dlgLogin;//登录界面的对象
    stuSql *m_ptrStuSql;//管理数据库
    Dlg_AddStu m_dlgAddStu;//添加界面对象
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>//需要在txt中去配置
#include <QDataWidgetMapper>//通过model映射到widget中
#include "tcomboboxdelegate.h"// 自定义代理

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QSqlDatabase DB;//用于建立与数据库的连接
    QSqlTableModel *tabModel;//编辑一个单一数据表的数据模型类
    QItemSelectionModel *selModel;//选择模型  跟踪视图中或同一模型上的多个视图中的选定项
    QDataWidgetMapper *dataMapper;//数据映射

    //两个代理
    TComboBoxDelegate delegateSex;//性别
    TComboBoxDelegate delegateDepart;//部门

    void openTable();//打开数据库表格
    void changeHeader();//改变数据库表头 英-->汉
    void setMapper();//建立映射关系

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //检查数据表的内容是否修改，更新按钮使能
    void do_currentChanged(const QModelIndex &current, const QModelIndex &previous);
    //行发生变化的时候，照片和备注也应该发生变化 从记录中判断是否具有数据
    void do_currentRowChanged(const QModelIndex &current, const QModelIndex &previous);

    void on_actOpenDB_triggered();//打开数据库

    void on_actRecAppend_triggered();//添加
    void on_actRecInsert_triggered();//插入
    void on_actRecDelete_triggered();//插入

    void on_actPhoto_triggered();//设置照片
    void on_actPhotoClear_triggered();//清除照片

    void on_actScan_triggered();//涨工资

    void on_actSubmit_triggered();//保存
    void on_actRevert_triggered();//取消

    void on_comSort_currentIndexChanged(int index);//选择字段排序
    void on_rbtnUp_clicked();//升序
    void on_rbtnDown_clicked();//降序

    //记录过滤 where操作 无需select刷新就可以显示
    void on_rbtnMan_clicked();
    void on_rbtnWoman_clicked();
    void on_rbtnAllDisplay_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

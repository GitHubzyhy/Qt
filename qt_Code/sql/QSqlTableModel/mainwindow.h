#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtSql>//需要在txt中去配置
#include<QDataWidgetMapper>//通过model映射到widget中
#include"tcomboboxdelegate.h"// 自定义代理

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
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

    void  openTable();//打开数据库表格
    void  changeHeader();//改变数据库表头 英-->汉
    void  setMapper();//建立映射关系

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actOpenDB_triggered();//复习顺序从这里开始！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
    void do_currentChanged(const QModelIndex &current,const QModelIndex &previous);
    void do_currentRowChanged(const QModelIndex &current,const QModelIndex &previous);

    void on_actRecAppend_triggered();

    void on_actRecInsert_triggered();

    void on_actRecDelete_triggered();

    void on_actPhoto_triggered();

    void on_actPhotoClear_triggered();

    void on_actScan_triggered();

    void on_actSubmit_triggered();

    void on_actRevert_triggered();

    void on_comSort_currentIndexChanged(int index);

    void on_rbtnUp_clicked();

    void on_rbtnDown_clicked();

    void on_rbtnMan_clicked();

    void on_rbtnWoman_clicked();

    void on_rbtnAllDisplay_clicked();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

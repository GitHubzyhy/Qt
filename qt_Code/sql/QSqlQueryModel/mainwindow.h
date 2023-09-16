#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtSql>//要在txt文件中配置
#include<QDataWidgetMapper>//数据源与小部件之间建立映射关系

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QSqlDatabase DB;//用于建立与数据库的连接
    QSqlQueryModel *qryModel;//只能查询不能编辑
    QItemSelectionModel *selModel;//选择模型  跟踪视图中或同一模型上的多个视图中的选定项
    QDataWidgetMapper *dataMapper;//数据映射

    void selectData();//调用select语句拿到数据显示在视图上面
    void headChange();//改变默认表头
    void setMapper();//映射
    void refreshTableView();//刷新
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actOpenDB_triggered();//打开数据库
    void on_actRectFirst_triggered();
    void on_actRectprevious_triggered();
    void on_actRectNext_triggered();
    void on_actRecLast_triggered();

    void on_currentRowChange(const QModelIndex &current, const QModelIndex &previous);//行发生变化时

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

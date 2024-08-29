#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>//需要在txt中配置

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
    QSqlQueryModel *qryModel;//只能查询不能编辑
    QItemSelectionModel *selModel;//选择模型  跟踪视图中或同一模型上的多个视图中的选定项

    void selectData();//打开数据表
    void headChange();//改变表头的字段   英文-->中文
    void updateRecord(int recNo);//更新记录
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actOpenDB_triggered();//打开数据库
    void on_actRecInsert_triggered();//插入记录
    void on_actRecEdit_triggered();//编辑记录
    void on_tableView_doubleClicked(const QModelIndex &index);//双击编辑
    void on_actRecDelete_triggered();//删除记录
    void on_actScan_triggered();//记录遍历(涨工资)

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

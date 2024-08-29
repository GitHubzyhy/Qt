#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class QLabel;
class QStandardItemModel;
class QItemSelectionModel;
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLabel *LabCellPos;//当前单元格行列号
    QLabel *LabCellText;//当前单元格内容
    QStandardItemModel *model;
    QItemSelectionModel *selectModel;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupModel();//模型初始化
    void initTable();//创建二维表
    void setItem(int row);//添加和插入行的时候需要的额外操作
    void initStatus();//状态栏初始化
    void updateSelect(const QModelIndex &index);//更新选择模型

private slots:
    void statusChange(const QModelIndex &current);//状态栏添加信息

    void on_act_addRow_triggered();//添加行
    void on_act_insertRow_triggered();//插入行
    void on_act_deleteRow_triggered();//删除行
    void resetTable(int rowCount); //表格复位

    void on_act_stm_open_triggered();//打开stm文件
    void on_act_stm_save_triggered();//保存stm文件
    void on_act_dat_open_triggered();//打开dat文件
    void on_act_dat_save_triggered();//保存dat文件

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

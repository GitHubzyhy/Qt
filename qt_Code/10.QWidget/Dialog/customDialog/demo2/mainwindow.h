#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#define ColumnCount 4//QTableView固定4列

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class QStandardItemModel;
class QItemSelectionModel;
class QWDialogHeaders;
class QWDialogLocate;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setACellText(int row, int column, QString text);//用于指定行，列的单元格文本
    void setDlgLocateNull();//将定位单元格指针设置为nullptr
    void setActLocateEnable(bool enable);//设置act_cell是否启用

private slots:
    void on_act_rowColumn_triggered();//设置行数 列数
    void on_act_title_triggered();//设置标题
    void on_act_cell_triggered();//定位单元格

    void on_tableView_clicked(const QModelIndex &index);//单击单元格

private:
    Ui::MainWindow *ui;

    QWDialogHeaders *dlgSetHeaders = nullptr;//设置标题的对话框
    QWDialogLocate *dlgLocate = nullptr;//非模态

    QStandardItemModel *theModel = nullptr;//数据模型
    QItemSelectionModel *selectModel = nullptr;//选择模型
    QStringList headList;//存放表头数据

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;//重写窗口关闭时触发的事件
};
#endif // MAINWINDOW_H

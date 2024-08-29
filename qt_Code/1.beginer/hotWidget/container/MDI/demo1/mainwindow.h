#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class QMdiSubWindow;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_act_new_triggered();//新建文档

    void on_act_open_triggered(); //打开文档

    void on_act_close_triggered();//关闭全部按钮的触发函数

    void on_act_cut_triggered();

    void on_act_copy_triggered();

    void on_act_paste_triggered();

    void on_act_font_triggered();

    void on_act_MDI_triggered(bool checked);//MDI模式

    void on_act1_triggered();//级联展开

    void on_act2_triggered();//平铺展开

    void on_mdiArea_subWindowActivated(QMdiSubWindow *arg1);////当前活动窗口切换时产生触发此信号函数，利用该信号函数可以在活动窗口切换时进行一些处理

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

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
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots://工具栏缩放函数
    void on_action_triggered();
    void on_action_2_triggered();
    void on_action_3_triggered();

private:
    Ui::MainWindow *ui;
    QLabel *labXYValue;//状态栏显示坐标标签
private:
    void createChart();//创建图表
    void prepareData();//准备数据
private slots://自定义槽函数
    void on_LegnedMarkerClicked();//图例单击槽函数，与图例mark的cliked()相关联,实现隐藏图例的功能
    void on_mouseMovePoint(QPoint point);//鼠标移动事件,时实显示鼠标光标处的坐标值
};
#endif // MAINWINDOW_H

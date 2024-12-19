#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class QGraphicsScene;
class QLabel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;//场景

    //状态栏内的标签
    QLabel *labViewCord;
    QLabel *labSceneCord;
    QLabel *labItemCord;

private:
    void iniGraphicsSystem();//创建Graphics View的各项

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void on_mouseMovePoint(QPoint point);//响应鼠标在视图上移动的事件信号，显示视图坐标和场景坐标
    void on_mouseClicked(QPoint point);//响应鼠标单击信号，显示图形项的局部坐标
};
#endif // MAINWINDOW_H

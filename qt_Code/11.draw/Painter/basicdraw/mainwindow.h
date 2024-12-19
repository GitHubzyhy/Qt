#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void add_Item();//负责初始化组合框
    void connect_All();//负责所有的信号槽

public slots:
    void shapeChanged();//改变形状
    void penChanged();//改变笔
    void brushChanged();//改变画刷

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

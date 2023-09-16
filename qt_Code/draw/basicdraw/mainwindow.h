#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void add_Item();//负责在组合框添加一个项
    void connect_All();//负责连接控件
public slots:
    void shapeChanged();//改变形状
    void penChanged();
    void brushChanged();

private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

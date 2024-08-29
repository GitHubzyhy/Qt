#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class QFormDoc;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void checkDialogClosed();//当主窗口隐藏，非模态对话框析构后，用来析构主窗口的
private:
    Ui::MainWindow *ui;
    int cnt;//用来判断非模态对话框的个数
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
private slots:
    void on_actWidgetInsite_triggered();
    void on_actWidget_triggered();
    void on_actWindowInsite_triggered();
    void on_actWindow_triggered();
    void on_tabWidget_tabCloseRequested(int index); //页面关闭的时候发射信号对应的槽函数
    void on_tabWidget_currentChanged(int index);//页面变化信号对应的槽函数
};
#endif // MAINWINDOW_H

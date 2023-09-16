#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPushButton;//向前申明，让其可以编译通过
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void onClick();//按钮被点击
    void onCheck(int);//被选中了
    QPushButton* clickBtn;
    QLabel *label;

    // QObject interface
protected:
    void timerEvent(QTimerEvent *event);
};
#endif // MAINWINDOW_H

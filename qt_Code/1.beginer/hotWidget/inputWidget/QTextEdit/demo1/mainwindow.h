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

private slots:
    void on_actionnew_triggered();//打开自定义对话框
    void on_actionprint_triggered();//打印

private:
    Ui::MainWindow *ui;
    void createLetter(const QString &name, const QString &address, //构造短信的内容
                      QList<QPair<QString, int>> orderitems,//这是表格项的内容
                      bool sendOffers);
};
#endif // MAINWINDOW_H

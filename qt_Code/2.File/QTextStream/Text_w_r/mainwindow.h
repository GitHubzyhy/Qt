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
private:
    QString getFile(bool save = false);
private slots:
    void on_actionQpen_IODevice_triggered();//QFIle打开

    void on_actSave_IODevice_triggered();//普通另存为

    void on_actSave_TextSafe_triggered();//更安全的另存

    void on_actOpen_TextStream_triggered();//用textStream打开文件

    void on_actSave_TextStream_triggered();//QTextStream另存

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

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

private slots:
    void on_actionnew_triggered();

    void on_actionprint_triggered();

private:
    Ui::MainWindow *ui;
    void createLetter(const QString &name,const QString &address,//构造短信的内容
                      QList<QPair<QString,int>> orderitems,
                      bool sendOffers);
};
#endif // MAINWINDOW_H

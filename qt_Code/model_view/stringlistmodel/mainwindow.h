#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QStringListModel;//申明
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_clear_clicked();

    void on_btn_delete_clicked();

    void on_btn_add_clicked();

    void on_btn_reset_clicked();

private:
    QStringListModel *model;//用来处理字符串列表的数据模型
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

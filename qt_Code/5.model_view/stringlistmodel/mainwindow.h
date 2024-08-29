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
    void on_btn_clear_clicked();//重置

    void on_btn_delete_clicked();//删除

    void on_btn_add_clicked();//添加

    void on_btn_reset_clicked();//修改

private:
    QStringListModel *model;//用来处理字符串列表的数据模型
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

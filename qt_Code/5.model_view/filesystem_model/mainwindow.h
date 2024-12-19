#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QFileSystemModel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_treeView_clicked(const QModelIndex &index);

private:
    QFileSystemModel *model;//访问本机文件系统的数据模型

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

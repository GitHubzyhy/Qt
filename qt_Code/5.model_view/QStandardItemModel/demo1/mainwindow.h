#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QStandardItemModel;//声明
class QDataWidgetMapper;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupModel();//初始化QStandardItemModel
    void updateButtons(int row);//越界和阴影选中

    QStandardItemModel *model;//基于项数据的标准数据模型
    QDataWidgetMapper *mapper;//数据模型和用户之间建立映射
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

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
    void setupModel();
    void updateButtons(int row);

    QStandardItemModel *model;
    QDataWidgetMapper *mapper;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <Qstringlistmodel.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(400, 300);
    setWindowIcon(QIcon("C:/Users/ZYH/Desktop/图片/图标/文件.png"));//设置图标
    setWindowTitle("这是一个demo");

    QStringList cities = { "北京", "上海", "广州", "深圳", "南京", "杭州" };
    model = new QStringListModel;
    model->setStringList(cities);//可以初始化数据模型的字符串列表的内容
    ui->listView->setModel(model);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不能编辑
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_clear_clicked()
{
    //改变数据在model里面找成员方法
    model->removeRows(0, model->rowCount()); //从0行开始删除n行

}

void MainWindow::on_btn_delete_clicked()
{
    QModelIndex index = ui->listView->currentIndex(); //获取当前选中的索引
    model->removeRow(index.row());//删除一行
}

void MainWindow::on_btn_add_clicked()
{
    model->insertRow(model->rowCount());//行是从0开始的 插入一行
    QModelIndex index = model->index(model->rowCount() - 1); //找到这里的索引
    model->setData(index, "new Item", Qt::DisplayRole); //第三个参数是指定显示方式
    ui->listView->edit(index);//可编辑的状态
}

void MainWindow::on_btn_reset_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    ui->listView->edit(index);//可编辑的状态
}

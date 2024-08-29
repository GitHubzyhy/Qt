#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QtWidgets>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon("C:/Users/ZYH/Desktop/图片/图标/file.png"));
    model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());//获取应用程序的当前目录 该目录不一定是可执行文件所在目录
    ui->treeView->setModel(model);
    ui->listView->setModel(model);

    connect(ui->treeView, &QTreeView::clicked,
            ui->listView, &QListView::setRootIndex);//用于设置listview的根索引
    //左边显示树状文件目录，右边只显示一列文件或者目录
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QString status = model->filePath(index); //通过索引（视图中的当前选定项）拿到路径

    if(!model->isDir(index))//判断是否是文件夹
    {
        status += " size: ";
        int size = model->size(index) / 1024;

        if(size < 1024) status += QString("%1KB").arg(size);
        else status += QString::asprintf("%.2fMB", size / 1024.0); //构建一个格式化字符串
    }

    statusBar()->showMessage(status);//显示路径`
}

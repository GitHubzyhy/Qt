#include "mainwindow.h"
#include<QApplication>
#include<QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QPixmap newpix("../exit.png");//加载图片并且转换成QPixmap，并且将其存储在newpix变量中

    QMenu *file=menuBar()->addMenu("&File");//获取窗口的菜单栏创建一个菜单添加到菜单栏中，&字符表示快捷键
    QAction *quit=new QAction(newpix,"&quit",this);
    quit->setShortcut(tr("CTRL+Q"));//tr() 函数对字符串进行国际化处理 创建快捷键

    status=new QAction("&View statusbar", this);
    status->setCheckable(true);
    status->setChecked(true);

    file->addAction(quit);
    file->addSeparator();//插入分割符
    file->addAction(status);
    connect(quit,&QAction::triggered,qApp,&QApplication::quit);
/*-----------------------------------------------------------------------------------*/
    QToolBar *toolbar = addToolBar("工具栏");//工具栏
    toolbar->addAction(quit);//工具栏里面添加项目
    toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);//文字显示在图标的下面
/*--------------------------------------------------------------------------------------*/
    statusBar();//返回主窗口的状态栏
    status->setStatusTip("状态栏");
    connect(status, &QAction::triggered,this, &MainWindow::toggleStatusbar);//判断是否显示状态栏的信息
    statusBar()->showMessage("已就绪");//状态栏中设置已就绪
    auto *edit = new QTextEdit(this);
    setCentralWidget(edit);
}

MainWindow::~MainWindow()
{
    delete status;
}

void MainWindow::toggleStatusbar()
{
    if (status->isChecked())//判断是否被选择
        statusBar()->show();
    else
        statusBar()->hide();

}


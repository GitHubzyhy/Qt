#include "mainwindow.h"
#include<QtWidgets>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMouseTracking(true);
    auto *quitBtn=new QPushButton("Quit",this);
    quitBtn->setGeometry(50,25,100,50);//在50，20哪个点上画一个100*50大小的按钮
    connect(quitBtn,&QPushButton::clicked,qApp,&QApplication::quit);//按钮按下程序就退出


}

MainWindow::~MainWindow()
{
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Escape)//如果按下esa键就退出整个程序
    {
        qApp->quit();//退出程序
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //获取x，y的坐标
    int x=event->pos().x();
    int y=event->pos().y();
    QString text="坐标"+QString::number(x)+","+QString::number(y);
    this->statusBar()->showMessage(text);//设置状态栏的文字为text
}


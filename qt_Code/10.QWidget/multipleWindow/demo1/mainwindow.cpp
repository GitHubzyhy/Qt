#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include "qformdoc.h"
#include "qformtable.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), cnt(0)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setVisible(false);//设置为不可见
    ui->tabWidget->clear();//清除所有页面
    ui->tabWidget->setTabsClosable(true); //Page有关闭按钮，可被关
    this->setWindowState(Qt::WindowMaximized); //窗口最大化显示
    this->setAutoFillBackground(true);//设置窗体自动填充背景
}

MainWindow::~MainWindow()
{
    QMessageBox::about(this, "析构消息",
                       "MainWindow被析构了！");
    delete ui;
}

void MainWindow::checkDialogClosed()
{
    bool isClose = false;
    cnt--;

    if(cnt == 0)//判断是否还有主窗口
        isClose = true;

    if(isClose && isVisible() == false)
    {
        setVisible(true);
        close();
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    //绘制窗口背景
    Q_UNUSED(event);//防止警告
    QPainter painter(this);//于绘图设备绑定
    painter.drawPixmap(0, ui->toolBar->height(), this->width(),
                       this->height() - ui->toolBar->height() -
                       ui->statusbar->height(), QPixmap(":/images/mainwindow/background.jpg"));
}

void MainWindow::on_actWidgetInsite_triggered()
{
    //创建QFormDoc窗体，并在tabWidget中显示
    QFormDoc *formDoc = new QFormDoc(this);
    formDoc->setAttribute(Qt::WA_DeleteOnClose);//关闭的时候自动删除
    int cur = ui->tabWidget->addTab(formDoc,
                                    QString::asprintf("Doc %d", ui->tabWidget->count())); //添加选项卡

    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);//将该控件设置为可见
}

void MainWindow::on_actWidget_triggered()
{
    //创建QFormDoc窗体，并在独立显示
    QFormDoc *formDoc = new QFormDoc(); //不指定父窗口，用show()显示
    formDoc->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    formDoc->setWindowTitle("基于QWidget的窗体，无父窗口，关闭时删除");

    formDoc->setWindowFlag(Qt::Window, true);

    formDoc->setWindowOpacity(0.9);//设置透明度
    formDoc->show();//非模态显示窗口
    connect(formDoc, &QFormDoc::dialogClose, this, &MainWindow::checkDialogClosed);
    cnt++;
}

void MainWindow::on_actWindowInsite_triggered()
{
    //嵌入式显示
    QFormTable *formTable = new QFormTable(this); //加入对象树
    formTable->setAttribute(Qt::WA_DeleteOnClose);//关闭的时候自动删除

    int cur = ui->tabWidget->addTab(formTable, QString::asprintf("Table %d", ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);//设置为可见
}

void MainWindow::on_actWindow_triggered()
{
    //独立显示
    QFormTable *formTable = new QFormTable(this);

    formTable->setAttribute(Qt::WA_DeleteOnClose); //对话框关闭时自动删除对话框对象,用于不需要读取返回值的对话框
    formTable->setWindowTitle("基于QMainWindow的窗口，指定父窗口，关闭时删除");

    formTable->show();
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    //页面关闭的时候发射信号对应的槽函数
    if(index < 0) //没有页的时候
        return;

    QWidget *aForm = ui->tabWidget->widget(index);
    aForm->close();//关闭窗口
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    // //页面变化信号对应的槽函数
    bool en = ui->tabWidget->count() > 0;
    ui->tabWidget->setVisible(en);//设置tabWidget是否可见
}

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qformdoc.h"
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);//设置窗口最大化
    ui->act_cut->setEnabled(false);
    ui->act_copy->setEnabled(false);
    ui->act_paste->setEnabled(false);
    ui->act_font->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_act_new_triggered()
{
    //新建文档
    QFormDoc *formDoc = new QFormDoc(this);
    ui->mdiArea->addSubWindow(formDoc);//将文档窗口添加到MDI中
    formDoc->show(); //显示MDI窗体 非模态
}

void MainWindow::on_act_open_triggered()
{
    //打开文档
    bool needNew = false; //是否需要新建子窗口
    QFormDoc *formDoc = nullptr;

    if(ui->mdiArea->subWindowList().count() > 0) //如有mdiArea组件中已经有窗口
    {
        formDoc = qobject_cast<QFormDoc *>(ui->mdiArea->activeSubWindow()->widget()); //获取当前鼠标所选中的窗口对象
        needNew = formDoc->isFileOpened(); //needNew为false，表示不需要新建子窗口
    }
    else
        needNew = true; //需要新建子窗口

    if(needNew) //如果需要新建窗口，那么新建窗口
    {
        formDoc = new QFormDoc(this);
        ui->mdiArea->addSubWindow(formDoc); //将新建的窗口变为当前的操作窗口
    }

    QString curPath = QDir::currentPath(); //返回应用程序当前工作目录
    QString aFileName = QFileDialog::getOpenFileName(this,
                        tr("打开一个文件"), curPath,
                        tr("C程序文件(*.h *.cpp);;所有文件(*.*)"));

    formDoc->loadFormFile(aFileName); //通过文件名加载文件内容
    formDoc->show(); //显示窗口

    ui->act_cut->setEnabled(true);
    ui->act_copy->setEnabled(true);
    ui->act_paste->setEnabled(true);
    ui->act_font->setEnabled(true);
}

void MainWindow::on_act_close_triggered()
{
    //关闭全部按钮的触发函数
    ui->mdiArea->closeAllSubWindows();//关闭全部子窗口
}

void MainWindow::on_act_cut_triggered()
{
    //获取当前的活动窗口
    QFormDoc *formDoc = (QFormDoc *)ui->mdiArea->activeSubWindow()->widget();
    formDoc->textCut();//剪切
}

void MainWindow::on_act_copy_triggered()
{
    QFormDoc *formDoc = (QFormDoc *)ui->mdiArea->activeSubWindow()->widget();
    formDoc->textCopy();
}

void MainWindow::on_act_paste_triggered()
{
    QFormDoc *formDoc = (QFormDoc *)ui->mdiArea->activeSubWindow()->widget();
    formDoc->textPaste();
}

void MainWindow::on_act_font_triggered()
{
    QFormDoc *formDoc = (QFormDoc *)ui->mdiArea->activeSubWindow()->widget();
    formDoc->setEditFont();
}

void MainWindow::on_act_MDI_triggered(bool checked)
{
    //MDI模式
    if(checked)
    {
        ui->mdiArea->setViewMode(QMdiArea::TabbedView);//tab多页显示模式
        ui->mdiArea->setTabsClosable(true); //页面可关闭
        //窗体不能够设置级联展开和平铺展开
        ui->act1->setEnabled(false);
        ui->act2->setEnabled(false);

    }
    else
    {
        ui->mdiArea->setViewMode(QMdiArea::SubWindowView); //子窗口模式
        //窗体可以设置级联展开和平铺展开
        ui->act1->setEnabled(true);
        ui->act2->setEnabled(true);
    }
}

void MainWindow::on_act1_triggered()
{
    //级联展开
    ui->mdiArea->cascadeSubWindows();
}

void MainWindow::on_act2_triggered()
{
    //平铺展开
    ui->mdiArea->tileSubWindows();
}

void MainWindow::on_mdiArea_subWindowActivated(QMdiSubWindow *arg1)
{
    //当前活动窗口切换时产生触发此信号函数，利用该信号函数可以在活动窗口切换时进行一些处理
    if(ui->mdiArea->subWindowList().count() == 0) //如果当前MDI中没有窗口了
    {
        //编辑按钮都不能使用
        ui->act_cut->setEnabled(false);
        ui->act_copy->setEnabled(false);
        ui->act_paste->setEnabled(false);
        ui->act_font->setEnabled(false);
        ui->statusbar->clearMessage();
    }
    else
    {
        //当窗口切换时，将当前活动的窗口打开的文件名显示到statusBar中
        QFormDoc *formDoc = static_cast<QFormDoc *>(
                                ui->mdiArea->activeSubWindow()->widget());
        ui->statusbar->showMessage(formDoc->currentFileName());
    }

}

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QMessageBox>
#include <QCloseEvent>
#include "qwdialogsize.h"
#include "qwdialogheaders.h"
#include "qwdialoglocate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    theModel = new QStandardItemModel(4, ColumnCount, this); //构造一个4*ColumnCount标准数据模型
    selectModel = new QItemSelectionModel(theModel); //让其与标准数据项模型绑定
    ui->tableView->setModel(theModel);//设置tableView的数据模型
    ui->tableView->setSelectionModel(selectModel);//设置tableView的选择模型

    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);//扩展模式
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);//选择整个项目

    headList << "Name" << "Sex" << "Age" << "Address";
    theModel->setHorizontalHeaderLabels(headList);//设置页眉
}

MainWindow::~MainWindow()
{
    delete ui;
}
//指定行列单元格文本
void MainWindow::setACellText(int row, int column, QString text)
{
    //用于指定行，列的单元格文本
    QModelIndex index = theModel->index(row, column);//获取指定行，列的索引
    selectModel->clearSelection();//清除选择模型中的选择
    selectModel->setCurrentIndex(index, QItemSelectionModel::SelectCurrent); //重新设置选择模型的选中的位置
    theModel->setData(index, text, Qt::DisplayRole); //将其设置为text

    theModel->item(row, column)->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
}
//将定位单元格指针设置为nullptr
void MainWindow::setDlgLocateNull()
{
    dlgLocate = nullptr;
}
//设置act_cell是否启用
void MainWindow::setActLocateEnable(bool enable)
{
    ui->act_cell->setEnabled(enable);
}
//设置列数行数
void MainWindow::on_act_rowColumn_triggered()
{
    //模态对话框用过后就删除
    QWDialogSize *dlg = new QWDialogSize(this);
    Qt::WindowFlags flags = dlg->windowFlags();//获取窗口属性
    dlg->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);//再当前属性的基础上再添加一个属性
    dlg->setRowColumn(theModel->rowCount(), theModel->columnCount()); //先用模型的行数和列数填充spinBox

    if (dlg->exec() == QDialog::Accepted) //模态对话框显示
    {
        //这时候在自定义对话框里面spinBox的值重新设置了主窗口的行和列
        theModel->setRowCount(dlg->rowCount());
        theModel->setColumnCount(dlg->columnCount());
    }
    else
    {
        delete dlg;
        return ;
    }

    delete dlg;//释放对话框对象
}
//设置标题
void MainWindow::on_act_title_triggered()
{
    //一次创建，多次调用，对话框狂关闭时只是隐藏
    //设置表头标题
    if (dlgSetHeaders == nullptr) //如果是第一次调用就初始化
        dlgSetHeaders = new QWDialogHeaders(this);

    //该for循环用来初始化dlgSetHeaders对话框的列表
    if (dlgSetHeaders->headerList().count() != theModel->columnCount())
    {
        QStringList strList;//用来保存表头标题

        for (int i = 0; i < theModel->columnCount(); ++i)
            strList.append(theModel->headerData(i, Qt::Horizontal,//将每一个表头标题都存储在strList
                                                Qt::DisplayRole).toString());

        dlgSetHeaders->setHeaderList(strList);//初始化数据模型
    }

    if (dlgSetHeaders->exec() == QDialog::Accepted) //以模态的方式打开
    {
        //这时候在自定义对话框里面QListView重新设置了主窗口的表头
        QStringList strList = dlgSetHeaders->headerList();
        theModel->setHorizontalHeaderLabels(strList);
    }
}
//定位设置单元格
void MainWindow::on_act_cell_triggered()
{
    //定位单元格
    ui->act_cell->setEnabled(false);//单元格Action点击调出对话框之后就不能再点击

    dlgLocate = new QWDialogLocate(this);
    dlgLocate->setAttribute(Qt::WA_DeleteOnClose);//设置对话框关闭时自动删除

    Qt::WindowFlags flags = dlgLocate->windowFlags(); //获取对话框已存在的标志
    dlgLocate->setWindowFlags(flags | Qt::WindowStaysOnTopHint);//窗口总是显示在上方

    //设置对话框中两个spinBox控件显示的最大值为QStandardItemModel数据模型的行数和列数
    dlgLocate->setSpinRange(theModel->rowCount(), theModel->columnCount());
    QModelIndex curIndex = selectModel->currentIndex(); //获取当前选择的模型索引

    if (curIndex.isValid())
        dlgLocate->setSpinValue(curIndex.row(), curIndex.column());//为对话框的两个spinBox控件初始化值

    dlgLocate->show();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    //单击单元格，将单元格的行号，列号设置到对话框上
    if (dlgLocate != nullptr) //说明对话框存在
        dlgLocate->setSpinValue(index.row(), index.column());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //窗口关闭时候询问是否退出
    QMessageBox::StandardButton reply = QMessageBox::question(this, tr("确认"), "确定要退出本程序",
                                        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    if (reply == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}

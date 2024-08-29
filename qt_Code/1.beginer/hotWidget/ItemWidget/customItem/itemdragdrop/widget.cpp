#include "widget.h"
#include "./ui_widget.h"
#include <QListWidget>//列表控件
#include <QTreeWidget>//树形控件
#include <QTableWidget>//表格控件

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //构造列表控件的条目
    for (int i = 0; i < 5; ++i)
    {
        QListWidgetItem *itemL = new QListWidgetItem(ui->listWidget);
        itemL->setText(tr("listItem %1").arg(i));
    }

    //设置树形控件2列
    ui->treeWidget->setColumnCount(2);
    //各列均匀拉伸
    ui->treeWidget->header()->setSectionResizeMode(QHeaderView::Stretch);//项目视图中使用的标题
    //树形控件构造条目
    for (int i = 0; i < 5; ++i)
    {
        QTreeWidgetItem *itemT = new QTreeWidgetItem(ui->treeWidget); //自动添加为顶级条目
        itemT->setData(0, Qt::DisplayRole, tr("treeItem %1, 0").arg(i) ); //设置通用数据
        itemT->setText(1, tr("t%1, 1").arg(i) );
    }

    //设置表格 3*3
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(3);
    //各列均匀拉伸
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //构造表格条目
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            QTableWidgetItem *itemTA = new QTableWidgetItem(tr("tableItem %1, %2").arg(i).arg(j));
            ui->tableWidget->setItem(i, j, itemTA);
        }

    //默认选中内部移动模式
    ui->radioButtonInter->setChecked(true);
    on_radioButtonInter_clicked(true);//启用内部移动
}

Widget::~Widget()
{
    delete ui;
}
//内部拖拽
void Widget::on_radioButtonInter_clicked(bool checked)
{
    if (checked) //选中状态
    {
        //列表控件启用内部移动
        ui->listWidget->setDragDropMode(QAbstractItemView::InternalMove);
        //树形控件启用内部移动
        ui->treeWidget->setDragDropMode(QAbstractItemView::InternalMove);
        //表格控件启用内部移动
        ui->tableWidget->setDragDropMode(QAbstractItemView::InternalMove);
    }
}
//跨界拖拽
void Widget::on_radioButtonOuter_clicked(bool checked)
{
    if (checked)
    {
        //列表控件启用跨界拖拽
        SetOuterDragDrop(ui->listWidget);
        //树形控件启用跨界拖拽
        SetOuterDragDrop(ui->treeWidget);
        //表格控件启用跨界拖拽
        SetOuterDragDrop(ui->tableWidget);
    }
}
//启用跨界拖拽
void Widget::SetOuterDragDrop(QAbstractItemView *view)
{
    view->setSelectionMode(QAbstractItemView::SingleSelection); //单选模式
    view->setDragEnabled(true); //可以拖出源条目
    view->viewport()->setAcceptDrops(true); //视口可以接收拖入
    view->setDropIndicatorShown(true); //启用拖拽的显示效果
    view->setDragDropMode(QAbstractItemView::DragDrop); //使用能拖能拽的模式
}

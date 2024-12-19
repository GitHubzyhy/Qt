#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QtWidgets>
#include"intspindelegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(500, 200); //设置
    setWindowTitle("this is a demo");

    setupModel();//model已经绑定了数据
    ui->tableView->setModel(model);
    //将列宽调整成自适应模式，确保内容完全可见 内容越宽列就越宽
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    QStringList headers = {"姓名", "电话", "年龄"};
    model->setHorizontalHeaderLabels(headers);//设置顶部列名字

    /*将 数 据 模 型 和 用 户 界 面 之 间 的 数 据 同 步*/
    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);//让其与之关联
    mapper->addMapping(ui->nameEdit, 0);//当数据模型中的数据发生变化时，这些部件就会自动更新
    mapper->addMapping(ui->phoneEdit, 1);
    mapper->addMapping(ui->ageSpinBox, 2);

    connect(ui->previousButton, &QPushButton::clicked,
            mapper, &QDataWidgetMapper::toPrevious);//使用模型前一行的数据填充小部件

    connect(ui->nextButton, &QAbstractButton::clicked,
            mapper, &QDataWidgetMapper::toNext);//使用下一行（列）的数据填充小部件

    connect(mapper, &QDataWidgetMapper::currentIndexChanged,
            this, &MainWindow::updateButtons);//当索引发生变化的时候

    connect(ui->tableView, &QTableView::clicked, //一旦tableView的索引变了，让其当前索引的模型数据填充小部件
            this, [this](const QModelIndex & index)
    {
        mapper->setCurrentIndex(index.row());
    });
    mapper->toFirst();//让其指定第一个，在model中拿出一组数据

    /*------------- 将 自 定 义  的 整 数 型 代 理 应 用 在 QTableView 控 件 的 第 2 列--------------------------------*/
    //以控制该列的数据展示和编辑方式。通过设置代理，你可以自定义列的外观和交互方式，使其适应特定的数据类型或需求。
    IntSpinDelegate *intSpinDelegate = new IntSpinDelegate(this);

    ui->tableView->setItemDelegateForColumn(2, intSpinDelegate); //index:2的列使用指定的代理

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModel()
{
    model = new QStandardItemModel(5, 3, this); //一般与QTableView组成model-view结构
    QStringList names{"张三", "李四", "王五", "丁一", "刘二" },
    phones{"18111111111", "18111111112", "18111111113", "18111111114", "18111111115"},
    ages{"20", "31", "32", "19", "26"};

    //将数据存入项中，并且添加每一个项
    for(int row = 0; row < 5; ++row)
    {
        QStandardItem *item = new QStandardItem(names[row]);
        model->setItem(row, 0, item);

        item = new QStandardItem(phones[row]);
        model->setItem(row, 1, item);

        item = new QStandardItem(ages[row]);
        model->setItem(row, 2, item);
    }
}

void MainWindow::updateButtons(int row)
{
    //设置按钮上下移动的时候是否越界
    ui->previousButton->setEnabled(row > 0);
    ui->nextButton->setEnabled(row < model->rowCount() - 1);

    //这里是阴影选中
    QModelIndex index = model->index(row, 0);
    ui->tableView->selectRow(index.row());//选中整行
}

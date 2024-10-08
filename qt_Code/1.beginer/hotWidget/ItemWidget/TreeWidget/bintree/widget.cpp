#include "widget.h"
#include "./ui_widget.h"
#include <QMessageBox>
#include <QTreeWidgetItem>//树形条目
#include <QTreeWidget>  //树形控件
#include <QTreeWidgetItemIterator> //树形迭代器

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置树形控件只有 1 列
    ui->treeWidget->setColumnCount(1);
    //创建A条目，添加到顶级条目
    QTreeWidgetItem *itemA = new QTreeWidgetItem;
    itemA->setData(0, Qt::DisplayRole, "A"); //用通用函数设置
    ui->treeWidget->addTopLevelItem(itemA);

    //创建 B、C条目，添加给 A
    QTreeWidgetItem *itemB = new QTreeWidgetItem();
    itemB->setText(0, "B");
    itemA->addChild( itemB );
    QTreeWidgetItem *itemC = new QTreeWidgetItem();
    itemC->setText(0, "C");
    itemA->addChild( itemC );

    //创建D、E条目，构造函数指定父条目为 B，自动设置父子关系
    QTreeWidgetItem *itemD = new QTreeWidgetItem(itemB);
    itemD->setText(0, "D");
    QTreeWidgetItem *itemE = new QTreeWidgetItem(itemB);
    itemE->setText(0, "E");

    //创建F、G条目，构造函数指定父条目为 C，自动设置父子关系
    QTreeWidgetItem *itemF = new QTreeWidgetItem(itemC);
    itemF->setText(0, "F");
    QTreeWidgetItem *itemG = new QTreeWidgetItem(itemC);
    itemG->setText(0, "G");

    //展开所有子孙节点
    ui->treeWidget->expandAll();
}

Widget::~Widget()
{
    delete ui;
}
//先序遍历
void Widget::on_pushButtonPreorder_clicked()
{
    //获取A条目
    QTreeWidgetItem *itemA = ui->treeWidget->topLevelItem(0);
    //先序遍历打印
    qDebug() << tr("先序遍历：");
    PreorderTraversal( itemA );
}

//先序遍历递归函数
void Widget::PreorderTraversal(QTreeWidgetItem *curItem)
{
    if (nullptr == curItem) return; // 空指针判断
    int nChildCount = curItem->childCount(); //子节点数目

    //递归层级截止判断
    if (nChildCount < 1) //叶子节点，直接打印
    {
        qDebug() << curItem->text(0);
        return; //干完活返回
    }

    //存在子节点，先序遍历是苦工代码在前
    //苦工代码，打印本节点文本
    qDebug() << curItem->text(0);

    //踢皮球代码
    for (int i = 0; i < nChildCount; ++i)
    {
        QTreeWidgetItem *curChild = curItem->child(i);
        PreorderTraversal(curChild);//转换到子节点的状态
    }
}
//后序遍历
void Widget::on_pushButtonPostorder_clicked()
{
    //获取A条目
    QTreeWidgetItem *itemA = ui->treeWidget->topLevelItem(0);
    qDebug() << tr("后序遍历：");
    PostorderTraversal( itemA );
}

//后序遍历递归函数
void Widget::PostorderTraversal(QTreeWidgetItem *curItem)
{
    if (nullptr == curItem) return; //空指针判断
    int nChildCount = curItem->childCount(); //子节点数目

    //递归层级截止判断
    if (nChildCount < 1) //叶子节点，直接打印后返回
    {
        qDebug() << curItem->text(0);
        return;//干完活返回
    }

    //存在子节点,后序递归是苦工代码在后，踢皮球代码在前
    //踢皮球代码
    for (int i = 0; i < nChildCount; ++i)
    {
        QTreeWidgetItem *curChild = curItem->child(i);
        PostorderTraversal(curChild);//转换到子节点的状态
    }

    //苦工代码，打印本节点文本
    qDebug() << curItem->text(0);
}
//中序遍历
void Widget::on_pushButtonMidorder_clicked()
{
    //获取A条目
    QTreeWidgetItem *itemA = ui->treeWidget->topLevelItem(0);
    //中序遍历打印
    qDebug() << tr("中序遍历：");
    MidorderTraversal( itemA );
}
//中序遍历递归函数
void Widget::MidorderTraversal(QTreeWidgetItem *curItem)
{
    if ( nullptr == curItem ) return; //空指针判断
    //子节点数目
    int nChildCount = curItem->childCount();
    //递归层级截止判断
    if ( nChildCount < 1) //叶子节点，直接干活并返回
    {
        qDebug() << curItem->text(0);
        return;//干完活返回
    }

    //存在子节点，中序是大儿子在前，苦工代码居中，小儿子在后
    //踢皮球代码 1 ，叫大儿子干活
    QTreeWidgetItem *bigSon = curItem->child(0);
    MidorderTraversal(bigSon);//递归调用 1

    //苦工代码
    //自己打印本节点文本 中间节点
    qDebug() << curItem->text(0);

    //踢皮球代码 2，叫剩下的儿子干活，剩下的儿子都算小儿子
    for (int i = 1; i < nChildCount; ++i)
    {
        QTreeWidgetItem *litteSon = curItem->child(i);
        MidorderTraversal(litteSon);//转换到子节点的状态
    }
}
//迭代器遍历
void Widget::on_pushButtonIterator_clicked()
{
    //获取A条目
    QTreeWidgetItem *itemA = ui->treeWidget->topLevelItem(0);
    //迭代器遍历打印
    qDebug() << tr("迭代器遍历：（同先序）");
    IteratorTraversal( itemA );
}

//迭代器遍历打印，迭代器使用的是先序遍历
void Widget::IteratorTraversal(QTreeWidgetItem *curItem)
{
    if ( nullptr == curItem ) return; //空指针判断

    //定义迭代器
    QTreeWidgetItemIterator it(curItem);
    while (*it)
    {
        //直接打印条目文本
        qDebug() << (*it)->text(0);
        ++it;
        /*  用 ++ 获取下一个条目，遍历过程迭代器自动控制
            当 *it 为空时，表示树节点遍历完毕*/
    }
}
//按层遍历
void Widget::on_pushButtonLevels_clicked()
{
    //获取A条目
    QTreeWidgetItem *itemA = ui->treeWidget->topLevelItem(0);
    //按层遍历打印
    qDebug() << tr("按层遍历：（没有回归的特性，使用队列实现）");
    LevelsTraversal( itemA );
}
//按层遍历打印
void Widget::LevelsTraversal(QTreeWidgetItem *curItem)
{
    if (nullptr == curItem) return;
    QList<QTreeWidgetItem *> list; //建立队列
    list.append(curItem);//添加子树根节点

    while (!list.isEmpty())
    {
        QTreeWidgetItem *itemFirst = list.takeFirst(); //删除列表中的第一个项目并返回
        qDebug() << itemFirst->text(0);

        //枚举 itemFirst 子节点数
        int nChildCount = itemFirst->childCount();
        for (int i = 0; i < nChildCount; ++i)
            list.append(itemFirst->child(i));//把子节点添加到队列
    }
}

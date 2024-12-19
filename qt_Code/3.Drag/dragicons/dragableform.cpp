#include "dragableform.h"
#include "ui_dragableform.h"
#include <QtWidgets>
#include <QDataStream>
#include <QMimeData>

DragableForm::DragableForm(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DragableForm)
{
    ui->setupUi(this);
    setAcceptDrops(true);//该小部件将接受拖放事件，并允许其他小部件将数据拖放到它上面。
}

DragableForm::~DragableForm()
{
    delete ui;
}

void DragableForm::mousePressEvent(QMouseEvent *event)
{
    QWidget *widget = childAt(event->position().toPoint()); //获取鼠标事件发生位置的顶级窗口部件,childAt() 函数用于查找在指定位置上的子部件（即直接作为其他部件的子级的部件），并返回指向该部件的指针。
    QLabel *child = dynamic_cast<QLabel *>(widget); //基类像派生类转换
    if (!child) //如果不是QLabel的子类就直接退出
        return;

    QPixmap pixmap = child->pixmap().scaled(child->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QByteArray itemDate;//用于存储序列后的程序
    QDataStream dateStream(&itemDate, QIODevice::WriteOnly); //写入itemDate，QDataStream 类提供了二进制数据的序列化和反序列化功能，使我们能够以跨平台的方式存储复杂的数据结构。
    //将 pixmap 和鼠标光标在 QLabel 部件中的相对位置序列化到 itemData 数组中
    dateStream << pixmap << QPoint(event->position().toPoint() - child->pos());

    QMimeData *mimeData = new QMimeData; //在拖放操作中传递数据的类。它可以包含多种数据格式，以满足不同的拖放目标的要求。
    mimeData->setData("application/x-dnditemdata", itemDate); //将通过序列化得到的数据 itemDate 设置到该对象中，以便在拖放操作中传递自定义数据。

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);//mimeData 设置为拖放操作中的数据源。
    drag->setPixmap(pixmap);//在拖动过程中，鼠标跟随着这个图像，提供了视觉上的拖动效果
    drag->setHotSpot(event->position().toPoint() - child->pos()); //拖动图像将以鼠标光标位置为中心进行拖动，提供了更直观的拖放体验。

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);//在tempPixmap设备上画画

    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127)); //让其有个拖拽效果

    painter.end();
    child->setPixmap(tempPixmap);//此时tempPixmap已经被设置成灰色了

    //执行了一个拖放操作，表示允许既执行复制操作，又执行移动操作。这里默认设置为复制
    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
        child->close();//关闭原来的label
    else//如果是复制
    {
        child->setPixmap(pixmap);//还原效果
    }
}

void DragableForm::dragEnterEvent(QDragEnterEvent *event)
{
    //检查事件中传递的数据（MIME 数据）是否包含特定的数据格式
    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        if (event->source() == this) //检查事件的源部件是否是当前部件
        {
            event->setDropAction(Qt::MoveAction);//设置拖放事件的操作类型为移动操作
            event->accept();//当前控件接受拖放操作
        }
        else
            event->acceptProposedAction();//拖放目标建议执行什么类型的拖放行为（复制、移动等），当前部件会接受该建议并执行相应的操作。
    }
    else
        event->ignore();//当前控件忽略该拖放操作，拖拽事件将继续传递给其他可能接收拖拽的控件。
}

void DragableForm::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        //开始解析数据,反序列化
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;//读取pixmap和鼠标光标在QLabel中的相对位置

        QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        newIcon->move(event->position().toPoint() - offset); //求出label的左上端点并将其移动到指定位置
        newIcon->show();//显示小部件

        if (event->source() == this) //检查事件的源部件是否是当前部件
        {
            //告诉原窗口部件可以删除原来的拖动项了
            event->setDropAction(Qt::MoveAction);//效果是暂时的
            event->accept();//表示当前部件接受了拖放操作，并愿意处理这个事件。这样，在鼠标释放时，拖放操作将继续执行，并将数据传递给拖放目标。
        }
        else
            //告诉原窗口部件可以删除原来的拖动项了
            event->acceptProposedAction();//拖放目标建议执行什么类型的拖放行为（复制、移动等），当前部件会接受该建议并执行相应的操作。

    }
    else
        event->ignore();
}

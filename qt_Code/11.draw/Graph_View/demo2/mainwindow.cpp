#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include <QGraphicsScene>//场景
#include <QGraphicsEllipseItem>
#include <QRandomGenerator>//随机数
#include <QGraphicsItemGroup>//图形项组
#include <QColorDialog>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    labViewCord = new QLabel("View 坐标");
    labViewCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labViewCord);

    labSceneCord = new QLabel("场景 坐标：");
    labSceneCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labSceneCord);

    labItemCord = new QLabel("Item 坐标：");
    labItemCord->setMinimumWidth(150);
    ui->statusbar->addWidget(labItemCord);

    labItemInfo = new QLabel("ItemInfo：");//存储的自定义信息
    labItemInfo->setMinimumWidth(200);
    ui->statusbar->addWidget(labItemInfo);

    scene = new QGraphicsScene(-300, -200, 600, 200);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setCursor(Qt::CrossCursor);
    ui->graphicsView->setMouseTracking(true);//设置鼠标跟踪
    //拖拽模式设置为橡皮筋矩形拖拽，以便用户可以在图形视图中绘制矩形来选择多个图形项。
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

    connect(ui->graphicsView, &QWGraphicsView::mouseMovePoint,
            this, &MainWindow::on_mouseMovePoint);
    connect(ui->graphicsView, &QWGraphicsView::mouseClicked,
            this, &MainWindow::on_mouseClicked);
    connect(ui->graphicsView, &QWGraphicsView::mouseDoubleClick,
            this, &MainWindow::on_mouseDoubleClick);
    connect(ui->graphicsView, &QWGraphicsView::keyPress,
            this, &MainWindow::on_keyPress);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//鼠标移动
void MainWindow::on_mouseMovePoint(QPoint point)
{
    //point是GraphicsView的坐标，物理坐标
    labViewCord->setText(QString::asprintf("View 坐标：%d,%d",
                                           point.x(), point.y()));
    QPointF pointScene = ui->graphicsView->mapToScene(point); //转换到scene坐标
    labSceneCord->setText(QString::asprintf("Scene 坐标：%.0f,%.0f",
                                            pointScene.x(), pointScene.y()));
}
//鼠标单击
void MainWindow::on_mouseClicked(QPoint point)
{
    QPointF pointScene = ui->graphicsView->mapToScene(point); //转换到scene坐标
    QGraphicsItem *item = scene->itemAt(pointScene, ui->graphicsView->transform());
    if (item != nullptr) //有图形项
    {
        QPointF pointItem = item->mapFromScene(pointScene); //图形项的局部坐标
        labItemCord->setText(QString::asprintf("Item 坐标: %.0f %.0f",
                                               pointItem.x(), pointItem.y()));
        labItemInfo->setText(item->data(ItemDesciption).toString()
                             + "，ItemId=" + item->data(ItemId).toString());
    }
}
//减少代码冗余
template<typename T>void setBrushColor(T *item)
{
    QColor color = item->brush().color();
    color = QColorDialog::getColor(color, nullptr, "选择颜色");
    if (color.isValid())
        item->setBrush(QBrush(color));
}

//鼠标双击
void MainWindow::on_mouseDoubleClick(QPoint point)
{
    QPointF pointScene = ui->graphicsView->mapToScene(point); //转换到scene坐标
    QGraphicsItem *item = scene->itemAt(pointScene, ui->graphicsView->transform());
    if (item == nullptr) return; //没有图形项

    switch (item->type())
    {
        case QGraphicsEllipseItem::Type://椭圆
        {
            QGraphicsEllipseItem *theItem = qgraphicsitem_cast<QGraphicsEllipseItem *>(item);
            setBrushColor(theItem);
            break;
        }
            //...其他图形项 不列举了
    }
}
//按键
void MainWindow::on_keyPress(QKeyEvent *event)
{
    int cnt = scene->selectedItems().count();
    if (cnt != 1) return; //没有选中的项，或选中的项大于1个

    QGraphicsItem *item = scene->selectedItems().at(0);
    switch (event->key())
    {
        case Qt::Key_Delete://删除
            scene->removeItem(item);
            break;
        case Qt::Key_Space://顺时针旋转90°
            item->setRotation(90 + item->rotation());
            break;
        case Qt::Key_PageUp://放大
            item->setScale(0.1 + item->scale());
            break;
        case Qt::Key_PageDown://缩小
            item->setScale(-0.1 + item->scale());
            break;
        case Qt::Key_Left://左移
            item->setX(-1 + item->x());
            break;
        case Qt::Key_Right://右移
            item->setX(1 + item->x());
            break;
        case Qt::Key_Up://上移
            item->setY(-1 + item->y());
            break;
        case Qt::Key_Down://下移
            item->setY(1 + item->y());
            break;
    }
}
//矩形
void MainWindow::on_actItem_Rect_triggered()
{

}
//椭圆
void MainWindow::on_actItem_Ellipse_triggered()
{
    QGraphicsEllipseItem *item = new QGraphicsEllipseItem(-50, -30, 100, 60);
    item->setFlags(QGraphicsItem::ItemIsMovable//可移动
                   | QGraphicsItem::ItemIsSelectable//可选择
                   | QGraphicsItem::ItemIsFocusable);//可获得焦点
    item->setBrush(QBrush(QColor("#55aa7f")));
    item->setZValue(++frontZ);//用于叠放顺序
    int randomX = QRandomGenerator::global()->bounded(100);
    int randomY = QRandomGenerator::global()->bounded(100);
    item->setPos(randomX - 50, randomY - 50);
    item->setData(ItemId, ++seqNum); //自定义数据，ItemId是键
    item->setData(ItemDesciption, "椭圆");

    scene->addItem(item);
    scene->clearSelection();//取消场景中所有已选择的图形项的选择状态，使得它们不再处于选中状态。
}
//圆形
void MainWindow::on_actItem_Circle_triggered()
{

}
//三角形
void MainWindow::on_actItem_Triangle_triggered()
{

}
//梯形
void MainWindow::on_actItem_Polygon_triggered()
{

}
//直线
void MainWindow::on_actItem_Line_triggered()
{

}
//文字
void MainWindow::on_actItem_Text_triggered()
{

}
//图片
void MainWindow::on_actItem_Pixmap_triggered()
{

}
//放大
void MainWindow::on_actZoomIn_triggered()
{
    int cnt = scene->selectedItems().count(); //有多少个选中的图形项
    if (cnt == 1)
    {
        QGraphicsItem *item = scene->selectedItems().at(0);
        item->setScale(0.1 + item->scale());
    }
    else//对绘图视图进行放大
        ui->graphicsView->scale(1.1, 1.1);
}
//缩小
void MainWindow::on_actZoomOut_triggered()
{
    int cnt = scene->selectedItems().count(); //有多少个选中的图形项
    if (cnt == 1)
    {
        QGraphicsItem *item = scene->selectedItems().at(0);
        item->setScale(item->scale() - 0.1);
    }
    else//对绘图视图进行缩小
        ui->graphicsView->scale(0.9, 0.9);
}
//逆时针旋转
void MainWindow::on_actRotateLeft_triggered()
{
    int cnt = scene->selectedItems().count();
    if (cnt == 1)
    {
        QGraphicsItem *item = scene->selectedItems().at(0);
        item->setRotation(-30 + item->rotation());
    }
    else
        ui->graphicsView->rotate(-30);
}
//顺时针旋转
void MainWindow::on_actRotateRight_triggered()
{
    int cnt = scene->selectedItems().count();
    if (cnt == 1)
    {
        QGraphicsItem *item = scene->selectedItems().at(0);
        item->setRotation(30 + item->rotation());
    }
    else
        ui->graphicsView->rotate(30);
}
//取消所有变换
void MainWindow::on_actRestore_triggered()
{
    int cnt = scene->selectedItems().count();
    if (cnt == 1)
    {
        QGraphicsItem *item = scene->selectedItems().at(0);
        item->resetTransform();
        qDebug() << "11";
    }
    else
        ui->graphicsView->resetTransform();
}
//图形项前置
void MainWindow::on_actEdit_Front_triggered()
{
    int cnt = scene->selectedItems().count();
    if (cnt > 0) //只处理选中的第一个图形项
    {
        QGraphicsItem *item = scene->selectedItems().at(0);
        item->setZValue(++frontZ);
    }
}
//图形项后置
void MainWindow::on_actEdit_Back_triggered()
{
    int cnt = scene->selectedItems().count();
    if (cnt > 0) //只处理选中的第一个图形项
    {
        QGraphicsItem *item = scene->selectedItems().at(0);
        item->setZValue(--backZ);
    }
}
//组合
void MainWindow::on_actGroup_triggered()
{
    int cnt = scene->selectedItems().count();
    if (cnt > 1)
    {
        //自己本身也是图形项
        QGraphicsItemGroup *group = new QGraphicsItemGroup;
        scene->addItem(group);//组合添加到场景中去
        for (int i = 0; i < cnt; ++i)
        {
            QGraphicsItem *item = scene->selectedItems().at(0);
            item->setSelected(false);//取消选中
            item->clearFocus();//取消焦点
            group->addToGroup(item);
        }
        group->setFlags(QGraphicsItem::ItemIsMovable
                        | QGraphicsItem::ItemIsSelectable
                        | QGraphicsItem::ItemIsFocusable);
        group->setZValue(++frontZ);
        scene->clearSelection();//清除所有选择
        group->setSelected(true);//选中
    }
}
//打散
void MainWindow::on_actGroupBreak_triggered()
{
    int cnt = scene->selectedItems().count();
    if (cnt == 1)
    {
        QGraphicsItemGroup *group = (QGraphicsItemGroup *) scene->selectedItems().at(0);
        scene->destroyItemGroup(group);
    }
}
//删除图形项
void MainWindow::on_actEdit_Delete_triggered()
{
    //删除所有选中的图形项
    int cnt = scene->selectedItems().count();
    if (cnt > 0)
        for (int i = 0; i < cnt; ++i)
        {
            QGraphicsItem *item = scene->selectedItems().at(0);
            scene->removeItem(item);//删除图形项
        }
}

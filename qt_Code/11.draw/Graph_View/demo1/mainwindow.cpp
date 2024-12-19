#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtWidgets>
#include"qwgraphicsview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    labViewCord = new QLabel("view 坐标", this);
    labViewCord->setMinimumWidth(150);//设置最小宽度
    ui->statusbar->addWidget(labViewCord);

    labSceneCord = new QLabel("Scence 坐标", this);
    labSceneCord->setMinimumWidth(150);//设置最小宽度
    ui->statusbar->addWidget(labSceneCord);

    labItemCord = new QLabel("Item 坐标", this);
    labItemCord->setMinimumWidth(150);//设置最小宽度
    ui->statusbar->addWidget(labItemCord);

    ui->View->setCursor(Qt::CrossCursor);//设置光标形状
    ui->View->setMouseTracking(true);//即使没有按下按钮，小部件也会接收鼠标移动事件。
    /*  将图形视图部件的拖拽模式设置为橡皮筋矩形拖拽，
        以便用户可以在图形视图中绘制矩形来选择多个图形项。*/
    ui->View->setDragMode(QGraphicsView::RubberBandDrag);

    connect(ui->View, &QWGraphicsView::mouseMovePoint,
            this, &MainWindow::on_mouseMovePoint);
    connect(ui->View, &QWGraphicsView::mouseClicked,
            this, &MainWindow::on_mouseClicked);
    iniGraphicsSystem();//创建GraphView的各项
}

MainWindow::~MainWindow()
{
    delete ui;
}
//鼠标移动事件，point是GraphicsView 的坐标，物理坐标
void MainWindow::on_mouseMovePoint(QPoint point)
{
    labViewCord->setText(QString::asprintf("View 坐标: %d,%d", point.x(), point.y()));
    QPointF pointScene = ui->View->mapToScene(point); //转换到Scene坐标
    labSceneCord->setText(QString::asprintf("Scene 坐标: %.0f %.0f",
                                            pointScene.x(), pointScene.y()));
}
//获取鼠标单机事件
void MainWindow::on_mouseClicked(QPoint point)
{
    QPointF pointScene = ui->View->mapToScene(point); //转换到Scene坐标
    QGraphicsItem *item = nullptr;//图形项将用于执行坐标映射。
    /*  用于获取指定场景坐标处的图形项,第二个参数是是图形视图的变换矩阵，变换矩阵
        描述了图形视图中的缩放、旋转和平移等变换操作。*/
    item = scene->itemAt(pointScene, ui->View->transform());
    if (item != nullptr)
    {
        //将场景坐标映射到图形项的本地坐标系中
        QPointF pointItem = item->mapFromScene(pointScene);
        labItemCord->setText(QString::asprintf("Item 坐标: %.0f %.0f",
                                               pointItem.x(), pointItem.y()));
    }
}
//窗口大小发生变化的时候，显示视图区域大小，以及场景信息
void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->labelViewSize->setText(QString::asprintf("Graphics View 坐标，左上角总是（0，0），"
                               "宽距=%d , 高度=%d", ui->View->width(), ui->View->height()));
    QRectF rectF = ui->View->sceneRect(); //返回scene的矩形区
    ui->labelSceneRect->setText(QString::asprintf("QGraphicsView::sceneRect="
                                "(left,Top,width,Height)=%.0f"
                                ",%.0f,%.0f,%.0f",
                                rectF.left(), rectF.top(), rectF.width(), rectF.height()));
}
//创建Graphics View的各项
void MainWindow::iniGraphicsSystem()
{
    //构造场景和多个其他图形项
    QRectF rect(-200, -100, 400, 200); //左上角坐标，宽度，高度
    scene = new QGraphicsScene(rect); //scene 逻辑坐标系定义
    ui->View->setScene(scene);

    //画一个矩形框，大小等于scene
    QGraphicsRectItem *item1 = new QGraphicsRectItem(rect);
    item1->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);//设置标志位
    QPen pen;
    pen.setWidth(2);//将笔的宽度设置为2像素
    item1->setPen(pen);
    scene->addItem(item1);//添加到场景中

    //画一个位于scene中心的椭圆，测试局部坐标
    QGraphicsEllipseItem *item2 = new QGraphicsEllipseItem(-100, -50, 200, 100);
    item2->setPos(0, 0); //设置坐标
    item2->setBrush(QBrush(Qt::blue));
    item2->setFlags(QGraphicsItem::ItemIsMovable
                    | QGraphicsItem::ItemIsSelectable
                    | QGraphicsItem::ItemIsFocusable);
    scene->addItem(item2);

    //画一个圆，中心在scene的边缘
    QGraphicsEllipseItem *item3 = new QGraphicsEllipseItem(-50, -50, 100, 100);
    item3->setPos(rect.right(), rect.bottom()); //圆心在右下角
    item3->setBrush(QBrush(Qt::red));
    item3->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    scene->addItem(item3);

    scene->clearSelection();//取消场景中所有已选择的图形项的选择状态，使得它们不再处于选中状态。
}

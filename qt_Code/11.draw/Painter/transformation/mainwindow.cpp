#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "renderarea.h"
#include <QComboBox>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* --------------   选 择  要 绘 制 的 内  容   -----------------------*/
    originalRenderArea = new RenderArea; //设置一个窗口
    shapeComboBox = new QComboBox;

    shapeComboBox->addItem(tr("Clock"));//下拉列表
    shapeComboBox->addItem(tr("House"));
    shapeComboBox->addItem(tr("Text"));
    shapeComboBox->addItem(tr("Truck"));

    connect(shapeComboBox, &QComboBox::activated, //当用户在组合框中选择一个项目时，就会发送这个信号
            this, &MainWindow::shapeSelected);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(originalRenderArea, 0, 0);
    layout->addWidget(shapeComboBox, 1, 0);

    for (int i = 0; i < NumTransformedAreas; ++i)
    {
        transformedRenderAreas[i] = new RenderArea;

        operationComboBoxes[i] = new QComboBox; //下拉列表
        operationComboBoxes[i]->addItem(tr("No transformation"));//向下拉列表中添加项 本地化处理
        operationComboBoxes[i]->addItem(tr("Rotate by 60\xC2\xB0"));
        operationComboBoxes[i]->addItem(tr("Scale to 75%"));
        operationComboBoxes[i]->addItem(tr("Translate by (50,50)"));

        //放到布局中
        layout->addWidget(transformedRenderAreas[i], 0, i + 1);
        layout->addWidget(operationComboBoxes[i], 1, i + 1);

        //添加信号槽
        connect(operationComboBoxes[i], &QComboBox::activated,
                this, &MainWindow::operationChanged);
    }

    centralWidget()->setLayout(layout);

    setupShapes();//准备好图形
    shapeSelected(0);//初始化
}

MainWindow::~MainWindow()
{
    delete ui;
}

//选择图形
void MainWindow::shapeSelected(int index)
{
    QPainterPath shape = shapes[index]; //从QList里面取拿这个值

    //图形设置成一摸一样的
    originalRenderArea->setShape(shape);
    for (int i = 0; i < NumTransformedAreas; ++i) //四张图的形状是一样的，所以要用for循环设置成相同的图形
        transformedRenderAreas[i]->setShape(shape);

}
//坐标轴操作
void MainWindow::operationChanged()
{
    QList<RenderArea::Operation> operations;//因为是叠加操作所以这里用的集合
    for (int i = 0; i < NumTransformedAreas; ++i)
    {
        int index = operationComboBoxes[i]->currentIndex(); //判断第i个组合框的哪个项被点击了
        operations.append(RenderArea::Operation(index));//这里是一个叠加操作，添加的选项是，经过强制转换的
        transformedRenderAreas[i]->setOperations(operations);//坐标轴改变
    }
}
//准备好相应的图形
void MainWindow::setupShapes()
{
    //卡车
    QPainterPath truck;

    truck.setFillRule(Qt::WindingFill);//设置填充样式

    //用于绘制路径的不同线段和移动绘制点到新的位置，从而定义了整个"卡车"图形的轮廓。
    truck.moveTo(0.0, 87.0);//将当前绘制点移动到指定位置
    truck.lineTo(0.0, 60.0);//从当前绘制点绘制一条直线到指定位置
    truck.lineTo(10.0, 60.0);
    truck.lineTo(35.0, 35.0);
    truck.lineTo(100.0, 35.0);
    truck.lineTo(100.0, 87.0);
    truck.lineTo(0.0, 87.0);

    truck.moveTo(17.0, 60.0);
    truck.lineTo(55.0, 60.0);
    truck.lineTo(55.0, 40.0);
    truck.lineTo(37.0, 40.0);
    truck.lineTo(17.0, 60.0);

    //在x，y位置上添加添加宽度高度为多少的椭圆
    truck.addEllipse(17.0, 75.0, 25.0, 25.0);
    truck.addEllipse(63.0, 75.0, 25.0, 25.0);

    //时钟
    QPainterPath clock;

    clock.addEllipse(-50.0, -50.0, 100.0, 100.0);
    clock.addEllipse(-48.0, -48.0, 96.0, 96.0);

    clock.moveTo(0.0, 0.0);
    clock.lineTo(-2.0, -2.0);
    clock.lineTo(0.0, -42.0);
    clock.lineTo(2.0, -2.0);
    clock.lineTo(0.0, 0.0);

    clock.moveTo(0.0, 0.0);
    clock.lineTo(2.732, -0.732);
    clock.lineTo(24.495, 14.142);
    clock.lineTo(0.732, 2.732);
    clock.lineTo(0.0, 0.0);

    //房子
    QPainterPath house;
    house.moveTo(-45.0, -20.0);
    house.lineTo(0.0, -45.0);
    house.lineTo(45.0, -20.0);
    house.lineTo(45.0, 45.0);
    house.lineTo(-45.0, 45.0);
    house.lineTo(-45.0, -20.0);
    /*  将给定矩形作为封闭子路径添加到此路径。
        矩形被添加为顺时针方向的一组线。添加矩形后，
        绘制路径的当前位置位于矩形的左上角。*/
    house.addRect(15.0, 5.0, 20.0, 35.0);
    house.addRect(-35.0, -15.0, 25.0, 25.0);

    //Qt文件
    QPainterPath text;
    QFont font;
    font.setPixelSize(50);//将字体设置为多大的像素
    /*  QFontMetrics是一个用于处理字体度量的工具类。
        boundingRect()函数返回了字符串"Qt"在指定字体下的外框矩形，
        即一个QRect对象，该矩形包围了"Qt"字符串的整个范围。*/
    QRect fontBoundingRect = QFontMetrics(font).boundingRect(tr("Qt"));
    //让Qt的方格子中心在0，0而不是0，0为左上角
    text.addText(-QPointF(fontBoundingRect.center()), font, tr("Qt"));

    //全部添加到集合中
    shapes.append(clock);
    shapes.append(house);
    shapes.append(text);
    shapes.append(truck);
}

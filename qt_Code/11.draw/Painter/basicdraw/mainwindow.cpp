#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    add_Item();//向组合框添加项
    connect_All();//创建所有的信号与槽函数

    shapeChanged();//改变形状
    penChanged();//改变笔的样式
    brushChanged();//改变画刷的特性
}

MainWindow::~MainWindow()
{
    delete ui;
}

//负责初始化组合框
void MainWindow:: add_Item()
{
    //向组合框中添加一个项
    //设置绘画的形状，绘画在renderarea，第二个参数是自定义数据与选项关联起来
    ui->shape->addItem(tr("Polygon"), RenderArea::Polygon); //第二个参数是枚举值
    ui->shape->addItem(tr("Rectangle"), RenderArea::Rect);
    ui->shape->addItem(tr("Rounded Rectangle"), RenderArea::RoundedRect);
    ui->shape->addItem(tr("Pie"), RenderArea::Pie);
    ui->shape->addItem(tr("Chord"), RenderArea::Chord);
    ui->shape->addItem(tr("Path"), RenderArea::Path);
    ui->shape->addItem(tr("Line"), RenderArea::Line);
    ui->shape->addItem(tr("Polyline"), RenderArea::PolyLine);
    ui->shape->addItem(tr("Text"), RenderArea::Text);
    ui->shape->addItem(tr("Pixmap"), RenderArea::Pixmap);

    //设置线条样式
    ui->penStyleComboBox->addItem(tr("Solid"), static_cast<int>(Qt::SolidLine));
    ui->penStyleComboBox->addItem(tr("Dash"), static_cast<int>(Qt::DashLine));
    ui->penStyleComboBox->addItem(tr("Dot"), static_cast<int>(Qt::DotLine));
    ui->penStyleComboBox->addItem(tr("Dash Dot"), static_cast<int>(Qt::DashDotLine));
    ui->penStyleComboBox->addItem(tr("Dash Dot Dot"), static_cast<int>(Qt::DashDotDotLine));
    ui->penStyleComboBox->addItem(tr("None"), static_cast<int>(Qt::NoPen));

    //设置线条端点样式
    ui->penCapComboBox->addItem(tr("Flat"), Qt::FlatCap);
    ui->penCapComboBox->addItem(tr("Square"), Qt::SquareCap);
    ui->penCapComboBox->addItem(tr("Round"), Qt::RoundCap);

    //设置线条连接样式
    ui->penJoinComboBox->addItem(tr("Miter"), Qt::MiterJoin);
    ui->penJoinComboBox->addItem(tr("Bevel"), Qt::BevelJoin);
    ui->penJoinComboBox->addItem(tr("Round"), Qt::RoundJoin);

    //设置画刷的填充特性
    ui->brushStyleComboBox->addItem(tr("Linear Gradient"),
                                    static_cast<int>(Qt::LinearGradientPattern));
    ui->brushStyleComboBox->addItem(tr("Radial Gradient"),
                                    static_cast<int>(Qt::RadialGradientPattern));
    ui->brushStyleComboBox->addItem(tr("Conical Gradient"),
                                    static_cast<int>(Qt::ConicalGradientPattern));
    ui->brushStyleComboBox->addItem(tr("Texture"), static_cast<int>(Qt::TexturePattern));
    ui->brushStyleComboBox->addItem(tr("Solid"), static_cast<int>(Qt::SolidPattern));
    ui->brushStyleComboBox->addItem(tr("Horizontal"), static_cast<int>(Qt::HorPattern));
    ui->brushStyleComboBox->addItem(tr("Vertical"), static_cast<int>(Qt::VerPattern));
    ui->brushStyleComboBox->addItem(tr("Cross"), static_cast<int>(Qt::CrossPattern));
    ui->brushStyleComboBox->addItem(tr("Backward Diagonal"), static_cast<int>(Qt::BDiagPattern));
    ui->brushStyleComboBox->addItem(tr("Forward Diagonal"), static_cast<int>(Qt::FDiagPattern));
    ui->brushStyleComboBox->addItem(tr("Diagonal Cross"), static_cast<int>(Qt::DiagCrossPattern));
    ui->brushStyleComboBox->addItem(tr("Dense 1"), static_cast<int>(Qt::Dense1Pattern));
    ui->brushStyleComboBox->addItem(tr("Dense 2"), static_cast<int>(Qt::Dense2Pattern));
    ui->brushStyleComboBox->addItem(tr("Dense 3"), static_cast<int>(Qt::Dense3Pattern));
    ui->brushStyleComboBox->addItem(tr("Dense 4"), static_cast<int>(Qt::Dense4Pattern));
    ui->brushStyleComboBox->addItem(tr("Dense 5"), static_cast<int>(Qt::Dense5Pattern));
    ui->brushStyleComboBox->addItem(tr("Dense 6"), static_cast<int>(Qt::Dense6Pattern));
    ui->brushStyleComboBox->addItem(tr("Dense 7"), static_cast<int>(Qt::Dense7Pattern));
    ui->brushStyleComboBox->addItem(tr("None"), static_cast<int>(Qt::NoBrush));
}
//负责所有的信号槽
void MainWindow::connect_All()
{
    //形状变化的型号槽
    connect(ui->shape, &QComboBox::activated, //选择一个项目的时候就会发出信号
            this, &MainWindow::shapeChanged);
    //笔的信号槽
    connect(ui->penWidthSpinBox, &QSpinBox::valueChanged,
            this, &MainWindow::penChanged);
    connect(ui->penStyleComboBox, &QComboBox::activated,
            this, &MainWindow::penChanged);
    connect(ui->penCapComboBox, &QComboBox::activated,
            this, &MainWindow::penChanged);
    connect(ui->penJoinComboBox, &QComboBox::activated,
            this, &MainWindow::penChanged);
    //笔刷的信号槽
    connect(ui->brushStyleComboBox, &QComboBox::activated,
            this, &MainWindow::brushChanged);

    /*------------     槽 函 数 是 RenderArea 中 的 类 成 员 函 数 --------------*/
    //抗锯齿的信号槽
    connect(ui->antialiasingCheckBox, &QAbstractButton::toggled,
            ui->renderAre, &RenderArea::setAntialiased);
    //是否旋转的信号槽
    connect(ui->transformationsCheckBox, &QAbstractButton::toggled,
            ui->renderAre, &RenderArea::setTransformed);
}
//改变形状
void MainWindow::shapeChanged()
{
    //在这里用于获取当前选中项的自定义数据。在Qt的数据模型中，
    //每个项都可以关联多个数据，而这些数据可以使用预定义的角色或自定义的角色来标识。
    int index = ui->shape->itemData(ui->shape->currentIndex(), Qt::UserRole).toInt();
    RenderArea::Shape shape = RenderArea::Shape(index);//转换为枚举类型

    ui->renderAre->setShap(shape);//改变形状
}
//改变笔
void MainWindow::penChanged()
{
    //获取线条的粗细
    int width = ui->penWidthSpinBox->value();
    //线条形状  用于获取当前选中项的关联数据
    Qt::PenStyle style = Qt::PenStyle(ui->penStyleComboBox->itemData(
                                          ui->penStyleComboBox->currentIndex(),
                                          Qt::UserRole).toInt());
    //线条端点
    Qt::PenCapStyle cap = Qt::PenCapStyle(ui->penCapComboBox->itemData(
            ui->penCapComboBox->currentIndex(), Qt::UserRole).toInt());
    //线条连接的样式
    Qt::PenJoinStyle join = Qt::PenJoinStyle(ui->penJoinComboBox->itemData(
                                ui-> penJoinComboBox->currentIndex(), Qt::UserRole).toInt());
    //构造具有指定笔刷、宽度、笔头样式、笔帽样式和连接样式的笔。
    ui->renderAre->setPen(QPen(Qt::blue, width, style, cap, join));
}
//改变画刷
void MainWindow::brushChanged()
{
    //获取当前ui文件内点击的画刷的样式
    Qt::BrushStyle style = Qt::BrushStyle(ui->brushStyleComboBox->itemData(
            ui-> brushStyleComboBox->currentIndex(), Qt::UserRole).toInt());

    if (style == Qt::LinearGradientPattern) //这里的是线性渐变
    {
        QLinearGradient linearGradient(0, 0, 100, 100);//在(x1, y1)和(x2, y2)之间构造具有插值区域的线性梯度。
        linearGradient.setColorAt(0.0, Qt::white);
        linearGradient.setColorAt(0.2, Qt::green);
        linearGradient.setColorAt(1.0, Qt::black);
        linearGradient.setSpread(QGradient::RepeatSpread);//设置延展方式
        ui->renderAre->setBrush(linearGradient);
    }
    else if (style == Qt::RadialGradientPattern) //这里是辐射渐变
    {
        QRadialGradient radialGradient(50, 50, 50, 70, 70);
        radialGradient.setColorAt(0.0, Qt::white);//设置渐变的起点坐标颜色
        radialGradient.setColorAt(0.2, Qt::green);
        radialGradient.setColorAt(1.0, Qt::black);//设置渐变的终点坐标颜色
        ui->renderAre->setBrush(radialGradient);
    }
    else if (style == Qt::ConicalGradientPattern) //这里的是圆锥形渐变
    {
        QConicalGradient conicalGradient(50, 50, 150);
        conicalGradient.setColorAt(0.0, Qt::white);
        conicalGradient.setColorAt(0.2, Qt::green);
        conicalGradient.setColorAt(1.0, Qt::black);
        ui->renderAre->setBrush(conicalGradient);
    }
    else if (style == Qt::TexturePattern)
        ui->renderAre->setBrush(QBrush(QPixmap(":/images/otherman.jpg").scaled(80, 80)));
    else
        ui->renderAre->setBrush(QBrush(Qt::green, style));
}

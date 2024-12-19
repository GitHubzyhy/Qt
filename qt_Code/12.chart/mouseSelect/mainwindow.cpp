#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include "qwchartview.h"
#include <QChartView>
#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
#include <QLegendMarker>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->layout()->setSpacing(20);	//设置部件之间的间隔

    labXYValue = new QLabel("X= , Y=");
    labXYValue->setMinimumWidth(200);//此属性保存小部件的最小宽度(以像素为单位)
    ui->statusbar->addWidget(labXYValue);//向状态栏中添加label

    createChart();//创建图表
    prepareData();//生成数据

    QChart *chart = ui->chartView->chart();
    //为每个marker的clicked信号关联自定义的槽函数
    foreach (QLegendMarker *marker, chart->legend()->markers())
    {
        qDebug() << "连接";
        connect(marker, &QLegendMarker::clicked, //为每一个marker的clicked信号关联自定义的槽函数
                this, &MainWindow::on_LegnedMarkerClicked);
    }
    connect(ui->chartView, &QWChartView::mouseMovePoint,
            this, &MainWindow::on_mouseMovePoint); //鼠标移动事件的信号槽连接
}

MainWindow::~MainWindow()
{
    delete ui;
}
//放大
void MainWindow::on_action_triggered()
{
    ui->chartView->chart()->zoom(1.2);
}
//缩小
void MainWindow::on_action_2_triggered()
{
    ui->chartView->chart()->zoom(0.8);
}
//原始大小
void MainWindow::on_action_3_triggered()
{
    ui->chartView->chart()->zoomReset();
}
//创建图表
void MainWindow::createChart()
{
    QChart *chart = new QChart;
    chart->setTitle("sin 和 cos曲线");
    chart->setAnimationOptions(QChart::SeriesAnimations);//设置动画效果
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);//设置抗锯齿
}
//准备数据
void MainWindow::prepareData()
{
    QChart *chart = ui->chartView->chart(); //从ui界面获取chart
    QLineSeries *sinSeries = new QLineSeries;
    QLineSeries *cosSeries = new QLineSeries;
    sinSeries->setName("sin曲线");//设置图例的名称
    cosSeries->setName("cos曲线");
    chart->addSeries(sinSeries);
    chart->addSeries(cosSeries);

    //序列添加数值
    qreal t = 0, y1, y2, intv = 0.1;
    for (int i = 0; i < 100; ++i)
    {
        y1 = qSin(t);
        sinSeries->append(t, y1); //在数据系列中添加一个数据点
        y2 = qSin(t + 20);
        cosSeries->append(t, y2);
        t += intv;
    }
    //创建数值坐标系
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, 10); //x轴的范围是0~10
    axisX->setTitleText("time(secs)");//标题

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(-2, 2);
    axisY->setTitleText("value");

    //为序列设置数值坐标轴 关联序列
    chart->setAxisX(axisX, sinSeries);
    chart->setAxisY(axisY, sinSeries);
    chart->setAxisX(axisX, cosSeries);
    chart->setAxisY(axisY, cosSeries);
    chart->setTitle("cin cos 曲线");
}
//单机图例的marker的响应
void MainWindow::on_LegnedMarkerClicked()
{
    qDebug() << "进入点击的槽函数内";
    //尝试将发送信号的对象转换为 QLegendMarker 类型
    QLegendMarker *marker = qobject_cast<QLegendMarker *>(sender());
    if (marker->type() == QLegendMarker::LegendMarkerTypeXY) //如果返回的序列是QLineSeries序列
    {
        marker->series()->setVisible(!marker->series()->isVisible());
        marker->setVisible(true);//总是设置为true，如果为false图例就隐藏了就无法实现用鼠标点击了
    }
}

void MainWindow::on_mouseMovePoint(QPoint point)//point是视图的坐标
{
    //鼠标移动的响应 并且试图坐标要转换成图表的数值
    QPointF pt = ui->chartView->chart()->mapToValue(point);
    labXYValue->setText(QString::asprintf("X=%.1f, Y=%.2f", pt.x(), pt.y()));
}

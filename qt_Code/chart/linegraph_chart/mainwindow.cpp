#include "mainwindow.h"
#include<QChartView>
#include<QLineSeries>
#include<QValueAxis>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{    //数据归chart管，显示的好不好看归View管
    setWindowTitle("简单折线图");

    QLineSeries *series=new QLineSeries();//创建了一个折线图数据序列
    //向数据系列添加一些数据点
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6)
            << QPointF(18, 3) << QPointF(20, 2);
    //要显示就必须将此数据系列添加到图表中进行可视化
    QChart *chart = new QChart();//图表
    chart->addSeries(series);//添加数据到图标
    chart->legend()->hide();//先拿到图例然后将图例隐藏。图例是对图标显示的序列的说明
    chart->createDefaultAxes();//用于在图表中创建默认的坐标轴
    chart->setTitle("Simple line chart example");

    QChartView *chartView=new QChartView(chart);//视图 显示数据
    chartView->setRenderHint(QPainter:: Antialiasing);//告诉画家打开抗锯齿

    setCentralWidget(chartView);//显示在中央控件中
  //  create();
}

MainWindow::~MainWindow()
{
}

void MainWindow::create()
{
    QChartView *chartView=new QChartView;
    QChart *chart=new QChart;//图表
    chartView->setChart(chart);

    this->setCentralWidget(chartView);//放到mainwindow的中央控件中

    //创建折线序列 序列用于存储显示的数据
    QLineSeries *sinSeries=new QLineSeries;
    QLineSeries *cosSeries=new QLineSeries;
    sinSeries->setName("sin 曲线");//设置图例名字
    cosSeries->setName("cos 曲线");
    chart->addSeries(sinSeries);
    chart->addSeries(cosSeries);
    //序列添加数值
    qreal t=0,y1,y2,intv=0.1;
    for(int i=0;i<100;++i)
    {
        y1=qSin(t);
        sinSeries->append(t,y1);//在数据系列中添加一个数据点
        y2=qSin(t+20);
        cosSeries->append(t,y2);
        t+=intv;
    }

    //创建数值坐标系
    QValueAxis *axisX=new QValueAxis;
    axisX->setRange(0,10);//x轴的范围是0~10
    axisX->setTitleText("time(secs)");//标题

    QValueAxis *axisY=new QValueAxis;
    axisY->setRange(-2,2);
    axisY->setTitleText("value");

    //为序列设置数值坐标轴
    chart->setAxisX(axisX,sinSeries);
    chart->setAxisY(axisY,sinSeries);
    chart->setAxisX(axisX,cosSeries);
    chart->setAxisY(axisY,cosSeries);
    chart->setTitle("cin cos 曲线");
}


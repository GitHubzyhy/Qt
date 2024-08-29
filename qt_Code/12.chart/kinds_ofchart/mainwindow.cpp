#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStandardItemModel>
#include <QTime>
#include <QBarSet>
#include <QLineSeries>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QPieSeries>//饼图序列
#include <QStackedBarSeries>
#include <QPercentBarSeries>
#include <QSplineSeries>
#include <QScatterSeries>//散点图

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    theModel = new QStandardItemModel(iniDataRowCount, fixedColumnCount, this); //几行几列的图表
    iniData();//初始化数据 学生姓名，成绩，平均分加入到表格
    surverData();//数据统计
    connect(theModel, &QStandardItemModel::itemChanged, //用于自动计算平均分
            this, &MainWindow::on_itemChanged);

    ui->tableView->setModel(theModel);//设置数据模型
    initKindsofChart("Barchart 演示", ui->chartViewBar); //柱状图初始化
    initKindsofChart("PieChart 演示", ui->chartViewPie); //饼图初始化
    initKindsofChart("Stackedchart 演示", ui->chartViewStackedBar); //堆叠柱状图初始化
    initKindsofChart("PercentBar 演示", ui->chartViewPercentBar); //百分比柱状图初始化
    initKindsofChart("ScatterChart演示", ui->chartViewScatterChart); //散点图初始化

}

MainWindow::~MainWindow()
{
    delete ui;
}
//数据初始化
void MainWindow::iniData()
{
    QStringList headerList;
    headerList << "姓名" << "数学" << "语文" << "英语" << "平均分";
    theModel->setHorizontalHeaderLabels(headerList);//设置表头文字
    srand(QTime::currentTime().second());//随机数种子

    for (int i = 0; i < theModel->rowCount(); i++)
    {
        QString studName = QString::asprintf("学生%2d", i + 1);
        QStandardItem *aItem = new QStandardItem(studName); //创建一个项
        aItem->setTextAlignment(Qt::AlignHCenter);//水平居中对齐

        theModel->setItem(i, colNoName, aItem); //学生列，设置item

        qreal avgScore = 0;
        //将随机生成的成绩的项添加到表格中，并且计算平均成绩
        for (int j = colNoMath; j <= colNoEnglish; ++j) //数学，语文，英语
        {
            //不包含最后一列（平均分）
            qreal score = 50.0 + (rand() % 50); //随机数字
            aItem = new QStandardItem(QString::asprintf("%.0f", score)); //让其不带小数
            aItem->setTextAlignment(Qt::AlignHCenter);//水平居中

            theModel->setItem(i, j, aItem); //加入一个项
            avgScore += score;
        }
        aItem = new QStandardItem(QString::asprintf("%.1f", avgScore / 3)); //计算平均分 保留一位小数字
        aItem->setTextAlignment(Qt::AlignHCenter);
        /*
            具体来说，如果 aItem->flags() 返回的标志值为 101010，并且 Qt::ItemIsEditable 的值是 001000，
            那么按位与操作的结果将是 101010 & 110111 = 100010，
            即移除了 Qt::ItemIsEditable 标志。
        */
        aItem->setFlags(aItem->flags() & (!Qt::ItemIsEditable));//不允许编辑

        theModel->setItem(i, colNoAverage, aItem); //将平均分这个项添加到表格
    }
}
//数据统计
void MainWindow::surverData()
{
    int cnt50, cnt60, cnt70, cnt80, cnt90;

    qreal sumV, minV, maxV;
    qreal val;
    QTreeWidgetItem *item = nullptr;

    int i, j;
    for (i = colNoMath; i <= colNoAverage; ++i)
    {
        //初始化
        sumV = cnt50 = cnt60 = cnt70 = cnt80 = cnt90 = 0;

        //找最大值和最小值
        for (j = 0; j < theModel->rowCount(); ++j)
        {
            val = theModel->item(j, i)->text().toDouble();
            if (0 == j)
            {
                minV = val;
                maxV = val;
            }
            if (val < minV)
                minV = val;
            if (val > maxV)
                maxV = val;
            sumV += val; //计算总和

            if (val < 60)
                cnt50++;
            else if ((val >= 60) && (val < 70))
                cnt60++;
            else if ((val >= 70) && (val < 80))
                cnt70++;
            else if ((val >= 80) && (val < 90))
                cnt80++;
            else
                cnt90++;
        }

        item = ui->treeWidget->topLevelItem(0); //返回给定索引处0的顶级项，如果项不存在则返回nullptr。
        item->setText(i, QString::number(cnt50)); //在给定索引处0的顶级项的第i列写cnt50有多少个人
        item->setTextAlignment(i, Qt::AlignHCenter);

        item = ui->treeWidget->topLevelItem(1); //60 树形视图中的第二个顶层项
        item->setText(i, QString::number(cnt60));
        item->setTextAlignment(i, Qt::AlignHCenter);

        item = ui->treeWidget->topLevelItem(2); //70
        item->setText(i, QString::number(cnt70));
        item->setTextAlignment(i, Qt::AlignHCenter);

        item = ui->treeWidget->topLevelItem(3); //80
        item->setText(i, QString::number(cnt80));
        item->setTextAlignment(i, Qt::AlignHCenter);

        item = ui->treeWidget->topLevelItem(4); //90
        item->setText(i, QString::number(cnt90));
        item->setTextAlignment(i, Qt::AlignHCenter);

        item = ui->treeWidget->topLevelItem(5); //average
        item->setText(i, QString::number(sumV / theModel->rowCount()));
        item->setTextAlignment(i, Qt::AlignHCenter);

        item = ui->treeWidget->topLevelItem(6); //max
        item->setText(i, QString::number(maxV));
        item->setTextAlignment(i, Qt::AlignHCenter);

        item = ui->treeWidget->topLevelItem(7); //min
        item->setText(i, QString::number(minV));
        item->setTextAlignment(i, Qt::AlignHCenter);
    }
}
//初始化各种各样的图表
void MainWindow::initKindsofChart(QString message, QChartView *view)
{
    QChart *chart = new QChart();
    chart->setTitle(message);
    chart->setAnimationOptions(QChart::SeriesAnimations);//设置动画效果
    view->setChart(chart);//设置显示的图表
    view->setRenderHints(QPainter:: Antialiasing);//设置抗锯齿
}
//构造柱状图
void MainWindow::buildBarChart()
{
    QChart *chart = ui->chartViewBar->chart(); //获取ChartView关联的chart
    chart->removeAllSeries();//删除所有序列
    chart->removeAxis(chart->axisX());//删除X轴
    chart->removeAxis(chart->axisY());//删除Y轴

    //创建三个QBarSet数据集,从数据模型的表头获取Name 一个柱状图由多个数据集构成
    QBarSet *setMath = new QBarSet(theModel->horizontalHeaderItem(colNoMath)->text());
    QBarSet *setChinese = new QBarSet(theModel->horizontalHeaderItem(colNoChinese)->text());
    QBarSet *setEnglish = new QBarSet(theModel->horizontalHeaderItem(colNoEnglish)->text());

    QLineSeries *line = new QLineSeries(); //折线序列用于显示平均分
    line->setName(theModel->horizontalHeaderItem(colNoAverage)->text());//设置图例的Name
    QPen pen;
    pen.setColor(Qt::red);//设置平均分的折线序列的颜色
    pen.setWidth(2);
    line->setPen(pen);

    for (int i = 0; i < theModel->rowCount(); ++i)
    {
        //从数据模型获取数据
        setMath->append(theModel->item(i, colNoMath)->text().toInt()); //数据集添加一个数值
        setChinese->append(theModel->item(i, colNoChinese)->text().toInt());
        setEnglish->append(theModel->item(i, colNoEnglish)->text().toInt());

        //例子（学生1,平均分)
        line->append(QPointF(i, theModel->item(i, colNoAverage)->text().toFloat()));
    }
    //创建一个柱状图序列QBarSeries，并添加三个数据集
    QBarSeries *series = new QBarSeries;
    series->append(setMath);
    series->append(setChinese);
    series->append(setEnglish);

    chart->addSeries(series);//添加柱状图序列
    chart->addSeries(line);//添加折线图序列
    //用于横坐标的字符串列表，即学生姓名
    QStringList categories;//种类
    for (int i = 0; i < theModel->rowCount(); ++i)
        categories << theModel->item(i, colNoName)->text();

    QBarCategoryAxis *axisX = new QBarCategoryAxis; //用于柱状图的横向坐标 类别坐标轴
    axisX->append(categories);//添加横坐标文字列表
    chart->setAxisX(axisX, series); //设置横坐标
    chart->setAxisX(axisX, line);
    axisX->setRange(categories.at(0), categories.at(categories.count() - 1));

    //数值型坐标作为纵坐标
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 100);
    axisY->setTitleText("分数");
    axisY->setTickCount(6);//设置了6个主刻度线
    axisY->setLabelFormat("%.0f");//标签格式
    chart->setAxisY(axisY, series); //柱状图序列添加到y轴
    chart->setAxisY(axisY, line);
    chart->legend()->setVisible(true);//显示图例
    chart->legend()->setAlignment(Qt::AlignBottom);//图例显示在下面
}
//饼图的构建 一个饼图由多个分块组成
void MainWindow::buildPieChart()
{
    QChart *chart = ui->chartViewPie->chart(); //从ui界面获取chart
    chart->removeAllSeries();
    chart->setTheme((QChart::ChartTheme)ui->comboBox_them->currentIndex());
    int colNo = 1 + ui->comboBox_course->currentIndex(); //+1的原因是索引是从0开始的

    QPieSeries *series = new QPieSeries; //创建饼图序列
    series->setHoleSize(ui->doubleSpinBox_holeSize->value());// 设置饼图中间空心的大小
    series->setPieSize(ui->doubleSpinBox_pieSize->value());// 设置饼的大小
    for (int i = 0; i <= 4; ++i) //添加分块数据
    {
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i); //返回给定索引处的顶级项
        series->append(item->text(0), item->text(colNo).toFloat()); //添加一个分块到饼图
    }

    QPieSlice *slice = nullptr; //饼图分块
    for (int i = 0; i <= 4; ++i) //设置每个分块的标签文字
    {
        slice = series->slices().at(i); //获取分块
        //设置图例label
        slice->setLabel(slice->label() + QString::asprintf(": %.0f人, %.1f%",
                        slice->value(), slice->percentage() * 100));
        connect(slice, &QPieSlice::hovered, //信号槽连接
                this, &MainWindow::on_PieSliceHightlight);
    }

    slice->setExploded(true);//最后一个分块设置为弹出状态
    series->setLabelsVisible(true);//必须添加完slice之后再进行设置

    chart->addSeries(series);//添加饼图序列
    chart->setTitle("Piechart------" + ui->comboBox_course->currentText()); //设置图表的标题
    chart->legend()->setVisible(true);//设置图例是可见的
    chart->legend()->setAlignment(Qt::AlignRight);
}
//绘制堆叠柱状图，与柱状图相比，除了用了QStackedBarSeries作为序列，其他几乎一样
void MainWindow::buildStackedBar()
{
    QChart *chart = ui->chartViewStackedBar->chart(); //从ui界面获取图表
    chart->removeAllSeries();
    chart->removeAxis(chart->axisX());//从图表中移除坐标轴。图表释放指定轴对象的所有权。
    chart->removeAxis(chart->axisY());

    //创建三门课程的数据集
    QBarSet *setMath = new QBarSet(theModel->horizontalHeaderItem(colNoMath)->text());
    QBarSet *setChinese = new QBarSet(theModel->horizontalHeaderItem(colNoChinese)->text());
    QBarSet *setEnglish = new QBarSet(theModel->horizontalHeaderItem(colNoEnglish)->text());

    for (int i = 0; i < theModel->rowCount(); ++i)
    {
        //添加数据到数据集
        setMath->append(theModel->item(i, colNoMath)->text().toInt());
        setChinese->append(theModel->item(i, colNoChinese)->text().toInt());
        setEnglish->append(theModel->item(i, colNoEnglish)->text().toInt());
    }

    // 创建QStackedBarSeries对象并且添加数据集
    QStackedBarSeries *series = new QStackedBarSeries;
    series->append(setMath);
    series->append(setChinese);
    series->append(setEnglish);

    series->setLabelsVisible(true);//显示每段的数值标签
    chart->addSeries(series);//添加序列到图标

    //创建横轴
    QStringList categories;
    for (int i = 0; i < theModel->rowCount(); ++i)
        categories << theModel->item(i, colNoName)->text();
    QBarCategoryAxis *axisX = new QBarCategoryAxis; //类别坐标 作为横轴
    axisX->append(categories);
    axisX->setRange(categories.at(0), categories.at(categories.count() - 1)); //设置坐标轴的范围
    chart->setAxisX(axisX, series);

    //数值坐标轴作为纵轴
    QValueAxis *axisY = new QValueAxis; //数值坐标轴，作为纵轴
    axisY->setRange(0, 300);
    axisY->setTitleText("总分");//设置Y轴的标题
    axisY->setTickCount(6);//设置主刻度线有6根
    axisY->setLabelFormat("%.0f");//不保留小数
    chart->setAxisY(axisY, series);

    chart->legend()->setVisible(true);//设置图例是可见的
    chart->legend()->setAlignment(Qt::AlignBottom);//设置图例在最下方

}
//绘制百分比柱状图
void MainWindow::buildPercentnBar()
{
    QChart *chart = ui->chartViewPercentBar->chart();
    chart->removeAllSeries();
    chart->removeAxis(chart->axisX());//从图表中移除坐标轴。图表释放指定轴对象的所有权。
    chart->removeAxis(chart->axisY());

    //创建数据集
    QBarSet *setMath = new QBarSet(theModel->horizontalHeaderItem(colNoMath)->text());
    QBarSet *setChinese = new QBarSet(theModel->horizontalHeaderItem(colNoChinese)->text());
    QBarSet *setEnglish = new QBarSet(theModel->horizontalHeaderItem(colNoEnglish)->text());
    QTreeWidgetItem *item = nullptr;
    QStringList categories;//等会用于作为横坐标
    for (int i = 0; i <= 4; ++i)
    {
        // 从分数段统计表里面获取数据
        item = ui->treeWidget->topLevelItem(i); //返回给定索引处的顶级项
        categories << item->text(0);

        //添加数据项到数据集中
        setMath->append(item->text(colNoMath).toFloat());
        setChinese->append(item->text(colNoChinese).toFloat());
        setEnglish->append(item->text(colNoEnglish).toFloat());
    }
    QPercentBarSeries *series = new QPercentBarSeries; //创建百分比柱状序列
    series->append(setMath);
    series->append(setChinese);
    series->append(setEnglish);
    series->setLabelsVisible(true);//显示百分比
    chart->addSeries(series);

    QBarCategoryAxis *axisX = new QBarCategoryAxis; //类别坐标作为横轴
    axisX->append(categories);//轴的最大值将被修改为categories.at(ategories.count()-1),重复的不会被追加
    axisX->setRange(categories.at(0), categories.at(categories.count() - 1));
    chart->setAxisX(axisX, series);

    QValueAxis *axisY = new QValueAxis; //数值坐标作为纵轴
    axisY->setRange(0, 100);
    axisY->setTitleText("百分比");
    axisY->setTickCount(6);//设置主刻度线为6个
    axisY->setLabelFormat("%.1f");//标签格式 保留一个小数

    chart->setAxisY(axisY, series);//y轴与序列关联起来

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
}

//这里使用的随机数，与前面的表格数据没有一点关系
void MainWindow::buildScatterChart()
{
    //绘制QScatterSeries和QSplineSeries
    QChart *chart = ui->chartViewScatterChart->chart();
    chart->removeAllSeries();
    chart->removeAxis(chart->axisX());//从图表中移除坐标轴。图表释放指定轴对象的所有权。
    chart->removeAxis(chart->axisY());

    QSplineSeries *seriesLine = new QSplineSeries; //光滑曲线序列
    seriesLine->setName("spline 光滑曲线");
    QPen pen;
    pen.setColor(Qt::blue);
    pen.setWidth(2);//设置线宽
    seriesLine->setPen(pen);

    QScatterSeries *series0 = new QScatterSeries; //散点序列
    series0->setName("散点");
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);//设置散点序列的数据点形状 圆形 | 矩形
    series0->setBorderColor(Qt::black);//设置数据点形状边框的颜色
    series0->setBrush(QBrush(Qt::red));
    series0->setMarkerSize(12);//设置数据点形状的大小

    srand(QTime::currentTime().second());//随机数字种子
    for (int i = 0; i < 10; ++i)
    {
        int x = (rand() % 20);
        int y = (rand() % 20);
        series0->append(x, y); //散点序列
        seriesLine->append(x, y); //光滑曲线序列
    }

    chart->addSeries(series0);
    chart->addSeries(seriesLine);

    chart->createDefaultAxes();//创建默认坐标轴
    chart->axisX()->setTitleText("X 轴");
    chart->axisX()->setRange(-2, 22);

    chart->axisY()->setTitleText("Y 轴");
    chart->axisY()->setRange(-2, 22);

    // 设置图例
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
}

//分数修改后自动计算平均分
void MainWindow::on_itemChanged(QStandardItem *item)
{
    if ((item->column() < colNoMath) || (item->column() > colNoEnglish))
        return;//如果被修改的item不是数学，语文，英语，就退出
    int rowNo = item->row(); //获取更改的项的行编号
    qreal avg = 0;
    QStandardItem *aItem;
    for (int i = colNoMath; i <= colNoEnglish; ++i)
    {
        //获取三个分数的和
        aItem = theModel->item(rowNo, i); //获取当前行的i列的数据项
        avg += aItem->text().toDouble();
    }
    avg /= 3; //计算平均分

    aItem = theModel->item(rowNo, colNoAverage); //获取平均分数据的item
    aItem->setText(QString::asprintf("%.1f", avg)); //保留一位小数
}
//鼠标移入，和移出的时候发送hovered()信号，动态设置exploded效果
void MainWindow::on_PieSliceHightlight(bool show)
{
    QPieSlice *slice = (QPieSlice *)sender(); //返回一个指向发送信号的对象的指针
    slice->setExploded(show);//设置分块是否是弹出的
}

void MainWindow::on_btn_flashBar_clicked()
{
    buildBarChart();
}

void MainWindow::on_action_init_triggered()
{
    iniData();
}

void MainWindow::on_action_survey_triggered()
{
    surverData();
}

void MainWindow::on_btn_flashPie_clicked()
{
    buildPieChart();
}

void MainWindow::on_btn_flashStackedBar_clicked()
{
    //刷新堆叠柱状图
    buildStackedBar();
}

void MainWindow::on_btn_flashPercentBar_clicked()
{
    //百分比柱状图的槽函数
    buildPercentnBar();
}

void MainWindow::on_btn_flashScatterChart_clicked()
{
    //散点图的槽函数
    buildScatterChart();
}

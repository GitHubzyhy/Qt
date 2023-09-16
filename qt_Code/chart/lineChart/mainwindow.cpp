#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QLineSeries>
#include<QValueAxis>
#include<QTime>
#include<random>
#include<QFontDialog>
#include<QColorDialog>
#include<QTimer>
#include<QLineSeries>
#include"dialogpen.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);//图标下方显示文字
    setWindowIcon(QIcon(":/images/lineChart.png"));
    setWindowTitle("折线图详细设计");
    createChart();
    prepareDate();
    updateFromChart();

    init();//初始化自定义默认主题，动画效果等
    resize(940,587);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//工具栏内项的槽函数--------------------------------------------------------------------------------
void MainWindow::on_actZoomOut_triggered()
{//必须在camke中配置环境
    /*通过自定义因子因子放大视图。大于1.0的因子会放大视图，而介于0.0和1.0之间的因子会缩小视图。*/
    ui->cView->chart()->zoom(0.8);
}

void MainWindow::on_actZoomIn_triggered()
{
    ui->cView->chart()->zoom(1.2);
}

void MainWindow::on_actReset_triggered()
{
    ui->cView->chart()->zoomReset();//重置
}

void MainWindow::on_actFlush_triggered()
{
    prepareDate();
}

//page_1对应的槽函数--------------------------------------------------------------------------------
void MainWindow::on_btn_set_clicked()//修改图表的title
{
    QChart *chart=ui->cView->chart();
    chart->setTitle(ui->lineEdit_title->text());

}

void MainWindow::on_btn_titleFont_clicked()//设置图表的titlefont
{
    QFont font=ui->cView->chart()->titleFont();
    bool ok=false;
    font=QFontDialog::getFont(&ok,font);
    if(ok)
        ui->cView->chart()->setTitleFont(font);//如果点击的是ok就用选中的字体
}

//设置图例显示在上 下 左 右
void MainWindow::on_rBtn_Up_clicked()
{
    ui->cView->chart()->legend()->setAlignment(Qt::AlignTop);
}

void MainWindow::on_rBtn_Down_clicked()
{
    ui->cView->chart()->legend()->setAlignment(Qt::AlignBottom);
}

void MainWindow::on_rBtn_Left_clicked()
{
    ui->cView->chart()->legend()->setAlignment(Qt::AlignLeft);
}

void MainWindow::on_rBtn_Right_clicked()
{
    ui->cView->chart()->legend()->setAlignment(Qt::AlignRight);
}

void MainWindow::on_checkBox_legend_clicked(bool checked)//图例可见
{
    ui->cView->chart()->legend()->setVisible(checked);
}

void MainWindow::on_checkBox_legendBG_clicked(bool checked)//图例背景可见
{
    ui->cView->chart()->legend()->setBackgroundVisible(checked);
}

void MainWindow::on_pBtn_Font_clicked()//设置图例的字体
{
    QFont font=ui->cView->chart()->legend()->font();
    bool ok=false;

    font=QFontDialog::getFont(&ok,font);//最开始选中的字体是font
    if(ok)
        ui->cView->chart()->legend()->setFont(font);
}

void MainWindow::on_pBtn_legendcolor_clicked()//设置图例的标签字体颜色
{
    QColor color=ui->cView->chart()->legend()->labelColor();//获取最初图例的颜色
    color=QColorDialog::getColor(color);

    if(color.isValid())//如果是有效颜色
        ui->cView->chart()->legend()->setLabelColor(color);
}

void MainWindow::on_pBtn_setMargin_clicked()
{
    QMargins mgs;//定义了一组四个边距;左、上、右和下，它们描述矩形周围边框的大小
    mgs.setTop(ui->spinBox_Up->value());
    mgs.setLeft(ui->spinBox_Left->value());
    mgs.setRight(ui->spinBox_Right->value());
    mgs.setBottom(ui->spinBox_Down->value());

    ui->cView->chart()->setMargins(mgs);//设置在图表中去
}

void MainWindow::on_comboBox_motion_currentIndexChanged(int index)
{
    //图表视图中的图表的动画选项设置为 index 指定的值
    ui->cView->chart()->setAnimationOptions((QChart::AnimationOptions)index);
    /*
    QChart::NoAnimation：无动画效果。
    QChart::GridAxisAnimations：仅对网格和坐标轴应用动画。
    QChart::SeriesAnimations：仅对数据序列应用动画。
    QChart::AllAnimations：对所有元素应用动画。
    */
}

void MainWindow::on_comboBox_theme_currentIndexChanged(int index)
{
    //将图表视图中的图表的主题设置为 index 指定的值
    ui->cView->chart()->setTheme((QChart::ChartTheme)index);
    /*
    QChart::ChartThemeLight：浅色主题。
    QChart::ChartThemeBlueCerulean：蓝色主题。
    QChart::ChartThemeDark：深色主题。
    QChart::ChartThemeBrownSand：棕色主题。
    QChart::ChartThemeBlueNcs：蓝色 NCS 主题。
    */
}

//page_2对应的槽函数--------------------------------------------------------------------------------
void MainWindow::on_sin_curve_clicked()
{
    if(ui->sin_curve->isChecked())//判断是否按下
        curSeries=(QLineSeries *)ui->cView->chart()->series().at(0);//返回的是QAbstractSeries类
    else
        curSeries=(QLineSeries *)ui->cView->chart()->series().at(1);

    //获取curSeries的值，设置标题名称，序列可见，点数据可见，透明度滑动条
    ui->line_name->setText(curSeries->name());//要么为sin要么为cos
    ui->checkBox_curve->setChecked(curSeries->isVisible());
    ui->checkBox_data->setChecked(curSeries->pointsVisible());//点数据可见
    ui->horizontalSlider->setValue(curSeries->opacity()*10);//设置透明度滑动条
    //当前数据系列的数据点标签可见性状态。
    ui->checkBox_pointLableVisible->setChecked(curSeries->pointLabelsVisible());
}

void MainWindow::on_cos_curve_clicked()
{
    on_sin_curve_clicked();
}

void MainWindow::on_pBtn_name_clicked()//设置图例的名字
{
    curSeries->setName(ui->line_name->text());//该名称显示在图例中
}

void MainWindow::on_checkBox_curve_clicked(bool checked)//曲线可见的checkBox
{
    curSeries->setVisible(ui->checkBox_curve->isChecked());//一旦未勾选，可能sin或者cos曲线就会隐藏
}

void MainWindow::on_checkBox_data_clicked(bool checked)//数据点可选的checkBox
{
    curSeries->setPointsVisible(ui->checkBox_data->isChecked());
}

void MainWindow::on_pBtn_color_clicked()//设置选中曲线颜色
{
    QColor color=curSeries->color();//返回当前序列的颜色
    color=QColorDialog::getColor(color);//打开颜色对话框，color是初始的颜色
    if(color.isValid())//如果返回的是有效的颜色
    {
        curSeries->setColor(color);
    }
}

void MainWindow::on_pBtn_pen_clicked()//设置选中曲线用什么笔，自定义对话框去设置
{
    bool ok=false;
    QPen pen=curSeries->pen();
    pen=DialogPen::getPen(pen,ok);//自定义对话框
    if(ok)
        curSeries->setPen(pen);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)//设置透明度
{
    curSeries->setOpacity(value/10.0);
}

void MainWindow::on_checkBox_pointLableVisible_clicked(bool checked)//设置选中曲线数据点标签是否可见
{
    curSeries->setPointLabelsVisible(checked);
}

void MainWindow::on_pBtn_LabelFont_clicked()//设置选中曲线数据点字体
{
    QFont font=curSeries->pointLabelsFont();//数据点标签的字体
    bool ok=false;
    font=QFontDialog::getFont(&ok,font);
    if(ok)
        curSeries->setPointLabelsFont(font);//设置数据点标签的字体
}

void MainWindow::on_pBtn_LabelColor_clicked()//设置选中曲线数据点的颜色
{
    QColor color=curSeries->pointLabelsColor();
    color=QColorDialog::getColor(color);
    if(color.isValid())
        curSeries->setPointLabelsColor(color);
}

void MainWindow::on_rBtn_Y_clicked()//设置选中曲线数据点的显示格式
{
    if(ui->rBtn_Y->isChecked())
        curSeries->setPointLabelsFormat("@yPoint");//设置数据点标签显示格式
    else
        curSeries->setPointLabelsFormat("(@xPoint,@yPoint)");
}

void MainWindow::on_rBtn_XY_clicked()
{
    on_rBtn_Y_clicked();
}

//page_3对应的槽函数--------------------------------------------------------------------------------
void MainWindow::on_rBtn_XAxies_clicked()//选择要操作的x轴或者y轴
{
    //设置坐标轴
    QList<QAbstractAxis*>axes;
    if(ui->rBtn_XAxies->isChecked())//选取操作的x轴或者y轴
        axes=ui->cView->chart()->axes(Qt::Horizontal);//返回附加到具有定向指定方向的系列系列的轴
    else
        axes=ui->cView->chart()->axes(Qt::Vertical);
    curAxis=(QValueAxis*)axes[0];

    //获取坐标轴属性，显示到界面上去
    ui->dSBox_minV->setValue(curAxis->min());//设置轴值范围显示到ui界面
    ui->dSBox_maxV->setValue(curAxis->max());

    ui->Axis_title->setText(curAxis->titleText());//设置坐标轴的标题
    ui->chk_scaleisVisible->setChecked(curAxis->labelsVisible());//设置坐标轴标题是否可见

    ui->chk_gridLineVisible->setChecked(curAxis->isGridLineVisible());//设置网格线是否可见

    ui->spinBox_Tickcount->setValue(curAxis->tickCount());//设置tick的个数
    ui->chk_TickLineIsVisible->setChecked(curAxis->isLineVisible());//设置tick线是否可见

    ui->spinBox_minorTickcount->setValue(curAxis->minorTickCount());//设置次刻度线的个数
    ui->chk_MinorTickLineIsVisible->setChecked(curAxis->isMinorGridLineVisible());//设置次刻度线是否可见

}
//开始设置ui界面手动点击后的操作
void MainWindow::on_rBtn_YAxies_clicked()
{
    on_rBtn_XAxies_clicked();
}

void MainWindow::on_Axis_isVisible_clicked(bool checked)//设置坐标轴是否可见，curAxies已经被手动选择了
{
    curAxis->setVisible(checked);
}

void MainWindow::on_Axis_range_clicked()//用ui界面的QSPinBox设置选中坐标轴的范围
{
    curAxis->setRange(ui->dSBox_minV->value(),ui->dSBox_maxV->value());
}

void MainWindow::on_Axis_setTitle_clicked()//设置选中坐标轴的标题
{
    curAxis->setTitleText(ui->Axis_title->text());
}

void MainWindow::on_Axis_font_clicked()
{
    bool ok=false;
    QFont font=curAxis->titleFont();
    font=QFontDialog::getFont(&ok,font);
    if(ok)
        curAxis->setTitleFont(font);
}

void MainWindow::on_Axis_titleIsVisible_clicked(bool checked)//设置坐标轴标题是否可见
{
    curAxis->setTitleVisible(checked);
}

void MainWindow::on_pBtn_style_clicked()//根据ui界面的lineEdit设置坐标轴标签的格式
{
    curAxis->setLabelFormat(ui->lineEdit_style->text());//根据输入框输入标签格式
}

void MainWindow::on_pBtn_Fontcolor_clicked()//设置轴刻度标签颜色
{
    QColor color=curAxis->labelsColor();
    color=QColorDialog::getColor(color);
    if(color.isValid())//如果返回的颜色有效
        curAxis->setLabelsColor(color);
}

void MainWindow::on_pBtn_setFont_clicked()//设置轴刻度标签字体
{
    QFont font=curAxis->labelsFont();
    bool ok=false;
    font=QFontDialog::getFont(&ok,font);
    if(ok)
        curAxis->setLabelsFont(font);
}

void MainWindow::on_chk_scaleisVisible_clicked(bool checked)//设置刻度标签是否可见
{
    curAxis->setTitleVisible(checked);
}

void MainWindow::on_chk_gridLineVisible_clicked(bool checked)//设置选中坐标轴网格线是否可见
{
    curAxis->setGridLineVisible(checked);
}

//设置选中坐标轴的网格线的笔或者颜色
void MainWindow::on_pBtn_gridLineColor_clicked()
{
    QColor color=curAxis->gridLineColor();
    color=QColorDialog::getColor(color);
    if(color.isValid())//如果是有效的
        curAxis->setGridLineColor(color);//设置坐标轴主刻度线对应的网格线的颜色
}

void MainWindow::on_pBtn_gridLinePen_clicked()
{
    bool ok=false;
    QPen pen=curAxis->gridLinePen();
    pen=DialogPen::getPen(pen,ok);//自定义对话框
    if(ok)
        curAxis->setGridLinePen(pen);
}

void MainWindow::on_spinBox_Tickcount_valueChanged(int arg1)//设置主刻度线
{
    curAxis->setTickCount(arg1);
}

void MainWindow::on_spinBox_minorTickcount_valueChanged(int arg1)//设置次刻度线
{
    curAxis->setMinorTickCount(arg1);
}

void MainWindow::on_chk_TickLineIsVisible_clicked(bool checked)//设置主刻度线是否可见
{
    curAxis->setLineVisible(checked);
}

void MainWindow::on_pBtn_linePen_clicked()//设置坐标轴线的笔
{
    bool ok=false;
    QPen pen=curAxis->linePen();
    pen=DialogPen::getPen(pen,ok);
    if(ok)
        curAxis->setLinePen(pen);
}

void MainWindow::on_pBtn_lineColor_clicked()//设置坐标轴的线条颜色，
{
    QColor color=curAxis->linePenColor();
    color=QColorDialog::getColor(color);
    if(color.isValid())
        curAxis->setLinePenColor(color);
}

void MainWindow::on_MinorTick_Color_clicked()//设置次刻度线对应的网格线颜色
{
    QColor color=curAxis->minorGridLineColor();
    color=QColorDialog::getColor(color);
    if(color.isValid())
        curAxis->setMinorGridLineColor(color);
}

void MainWindow::on_pBtn_minorLinePen_clicked()
{
    bool ok=false;
    QPen pen=curAxis->gridLinePen();
    pen=DialogPen::getPen(pen,ok);
    if(ok)
        curAxis->setMinorGridLinePen(pen);
}

void MainWindow::on_chk_MinorTickLineIsVisible_clicked(bool checked)//设置选中坐标轴的次网格线是否可见
{
    curAxis->setMinorGridLineVisible(checked);
}

/*----------------           槽 函 数 实 现 完 毕                      ---------------- */
void MainWindow::createChart()
{
    QChart *chart=new QChart();
    chart->setTitle("simple curve");
    ui->cView->setChart(chart);//设置图表
    ui->cView->setRenderHint(QPainter:: Antialiasing);//绘制的时候抗锯齿

    //设置折线序列
    QLineSeries *sinSeries=new QLineSeries;
    QLineSeries *cosSeries=new QLineSeries;
    sinSeries->setName("sin");//设置图例的名称
    cosSeries->setName("cos");
    curSeries=sinSeries;//这里默认为sin曲线的信息，方便后续槽函数的使用

    //设置sin曲线绘画时候的笔
    QPen pen;
    pen.setStyle(Qt::DotLine);
    pen.setWidth(2);//设置笔的宽度
    sinSeries->setPen(pen);
    //设置cos曲线绘画时候的笔
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::blue);
    cosSeries->setPen(pen);

    chart->addSeries(sinSeries);
    chart->addSeries(cosSeries);

    //坐标轴设置
    QValueAxis *axisX=new QValueAxis;//用于控制横坐标刻度和标签的显示。
    QValueAxis *axisY=new QValueAxis;
    curAxis=axisX;//这里默认设置为x轴 方便后续槽函数的使用
    //x轴设置
    axisX->setRange(0,10);
    axisX->setLabelFormat("%.1f");//设置标签轴的坐标格式，浮点数格式化，保留一位小数。让其更精确
    axisX->setTickCount(11);//设置11个刻度数量
    axisX->setMinorTickCount(4);//每个主刻度之间显示 4 个次刻度。
    axisX->setTitleText("time(secs)");
    //y轴设置
    axisY->setRange(-1.5,1.5);
    axisY->setTickCount(3);
    axisY->setMinorTickCount(4);
    axisY->setTitleText("value");
    //用于将一个坐标轴（Axis）与一个数据序列（Series）关联起来，以便在图表中显示数据时，使用这个坐标轴来表示数据的横坐标。
    chart->setAxisX(axisX,sinSeries);
    chart->setAxisY(axisY,sinSeries);

    chart->setAxisX(axisX,cosSeries);
    chart->setAxisY(axisY,cosSeries);
}

void MainWindow::prepareDate()
{
    QLineSeries *sinSeries=(QLineSeries *)ui->cView->chart()->series().at(0);
    QLineSeries *cosSeries=(QLineSeries *)ui->cView->chart()->series().at(1);
    sinSeries->clear();
    cosSeries->clear();

    //生成数据点，并且添加到序列中
    srand(QTime::currentTime().second());
    qreal t=0,y1,y2,inv=0.1;
    qreal rd;
    for(int i=0;i<100;++i)
    {
        rd=(rand()%10)-5;
        y1=qSin(t)+rd/50;
        sinSeries->append(t,y1);//将数据点添加到序列中

        y2=qCos(t)+rd/50;
        cosSeries->append(t,y2);
        t+=inv;
    }
}

void MainWindow::updateFromChart()
{
    QChart *chart=ui->cView->chart();
    ui->lineEdit_title->setText(chart->title());//设置ui界面的title

    QMargins mg=chart->margins();//获取图表的外边距值。返回一个 QMargins 对象，其中包含了图表的上、下、左、右四个方向上的边距值。
    ui->spinBox_Down->setValue(mg.bottom());//设置为图标下边距的值
    ui->spinBox_Left->setValue(mg.left());
    ui->spinBox_Right->setValue(mg.right());
    ui->spinBox_Up->setValue(mg.top());

}

void MainWindow::init()
{
    //自动刷新
    QTimer *timer=new QTimer(this);
    connect(timer,&QTimer::timeout,//定时器超时就发出信号
            this,&MainWindow::prepareDate);
    timer->start(100);//启动或重新启动定时器，超时时间间隔为100毫秒。

    ui->comboBox_motion->setCurrentIndex(2);//QCombox也显示指定的动画效果
    ui->comboBox_theme->setCurrentIndex(1);//设置默认指定主题

}

void MainWindow::on_Axis_titlesVisible_clicked(bool checked)
{
    curAxis->setTitleVisible(checked);
}


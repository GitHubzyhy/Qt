#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class QLineSeries;
class QValueAxis;
class QLabel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    //工具栏内项的槽函数---------------------------------------------------------------------------------
    void on_actZoomOut_triggered();//缩小
    void on_actZoomIn_triggered();//放大
    void on_actReset_triggered();//原始大小
    void on_actFlush_triggered();//刷新绘图

    //page_1对应的槽函数---------------------------------------------------------------------------------
    void on_btn_set_clicked();//修改图表的title
    void on_btn_titleFont_clicked();//设置图表的titlefont
    // 设置图例在哪个位置
    void on_rBtn_Up_clicked();
    void on_rBtn_Down_clicked();
    void on_rBtn_Left_clicked();
    void on_rBtn_Right_clicked();

    void on_checkBox_legend_clicked(bool checked);//图例可见
    void on_checkBox_legendBG_clicked(bool checked);//图例背景可见

    void on_pBtn_Font_clicked();//设置图例的字体
    void on_pBtn_legendcolor_clicked();//设置图例的标签字体颜色
    void on_pBtn_setMargin_clicked();//设置边距
    void on_comboBox_motion_currentIndexChanged(int index);//设置动画效果
    void on_comboBox_theme_currentIndexChanged(int index);//设置主题

    //page_2对应的槽函数---------------------------------------------------------------------------------
    //设置选择哪条操作曲线
    void on_sin_curve_clicked();
    void on_cos_curve_clicked();

    void on_pBtn_name_clicked();//根据ui界面的editLine设置图例的名字
    void on_checkBox_curve_clicked(bool checked);//曲线可见的checkBox
    void on_checkBox_data_clicked(bool checked);//数据点是否可见
    void on_pBtn_color_clicked();//设置选中曲线颜色
    void on_pBtn_pen_clicked();//设置选中曲线用什么笔，自定义对话框去设置
    void on_horizontalSlider_valueChanged(int value);//设置透明度
    void on_checkBox_pointLableVisible_clicked(bool checked);//设置选中曲线数据点标签是否可见
    void on_pBtn_LabelFont_clicked();//设置选中曲线数据点字体
    void on_pBtn_LabelColor_clicked();//设置选中曲线数据点颜色
    //设置选中曲线数据点的显示格式 format
    void on_rBtn_Y_clicked();
    void on_rBtn_XY_clicked();

    //page_3对应的槽函数---------------------------------------------------------------------------------
    //选择要操作的x轴或者y轴
    void on_rBtn_XAxies_clicked();
    void on_rBtn_YAxies_clicked();

    void on_Axis_isVisible_clicked(bool checked);//设置坐标轴是否可见，curAxies已经被手动选择了
    void on_Axis_range_clicked();//用ui界面的QSPinBox设置选中坐标轴的范围
    void on_Axis_setTitle_clicked();//设置选中坐标轴的标题
    void on_Axis_font_clicked();//设置坐标轴标题的字体
    void on_pBtn_style_clicked();//设置坐标轴标签的格式
    //设置轴刻度颜色和字体
    void on_pBtn_Fontcolor_clicked();
    void on_pBtn_setFont_clicked();

    void on_chk_scaleisVisible_clicked(bool checked);//设置轴标题是否可见
    void on_chk_gridLineVisible_clicked(bool checked);//设置选中坐标轴主网格线是否可见
    //设置选中坐标轴的主网格线的笔或者颜色
    void on_pBtn_gridLineColor_clicked();
    void on_pBtn_gridLinePen_clicked();

    void on_spinBox_Tickcount_valueChanged(int arg1);//设置主刻度线个数
    void on_spinBox_minorTickcount_valueChanged(int arg1);//设置次刻度线个数
    void on_chk_TickLineIsVisible_clicked(bool checked);//设置轴线是否可见
    void on_pBtn_linePen_clicked();//设置轴线的笔
    void on_pBtn_lineColor_clicked();//设置轴线的颜色
    void on_MinorTick_Color_clicked();//设置次网格对应的笔
    void on_pBtn_minorLinePen_clicked();//设置次网格对应的笔
    void on_chk_MinorTickLineIsVisible_clicked(bool checked);//设置选中坐标轴的次网格是否可见

    void on_Axis_titlesVisible_clicked(bool checked);//轴标题可见

private:
    Ui::MainWindow *ui;

    QLineSeries *curSeries;//创建一个折线图的序列
    QValueAxis *curAxis;//数值坐标轴类

    void createChart();//创建坐标轴，和将未初始化的series加入到chart中
    void prepareDate();//从视图中获取series，并且初始化series
    void updateFromChart();// 在ui界面显示默认的值，比如边距的值，或者title
    void init();//设置默认效果---默认主题，默认动画效果 时间急可不看

};
#endif // MAINWINDOW_H

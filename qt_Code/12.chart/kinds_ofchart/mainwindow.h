#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

#define fixedColumnCount 5//数据模型的列数
#define iniDataRowCount 6//学生个数
#define colNoName 0//姓名的列编号
#define colNoMath 1//数学的列编号
#define colNoChinese 2 //语文的列编号
#define colNoEnglish 3//英语的列编号
#define colNoAverage 4//平均分的列编号

class QStandardItemModel;
class QStandardItem;
class QChartView;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void iniData();//初始化数据 学生姓名，成绩，平均分加入到表格
    void surverData();//统计数据

    void initKindsofChart(QString message, QChartView *view); //根据参数初始化各种各样的图表

    void buildBarChart();//构建柱状图
    void buildPieChart();//构建饼图
    void buildStackedBar();//构建堆叠图
    void buildPercentnBar();//构建百分比图
    void buildScatterChart();//构建散点图
private slots:
    // 三个分数列的数据发生变化，重新计算平均分
    //用于接受QStandardItemModel的itemChanged()信号
    void on_itemChanged(QStandardItem *item);

    //工具栏的两项
    void on_action_init_triggered();//数据初始化
    void on_action_survey_triggered();//数据统计

    void on_PieSliceHightlight(bool show); //饼图的鼠标放上去的槽函数

    //刷新图表用的槽函数
    void on_btn_flashBar_clicked();
    void on_btn_flashPie_clicked();
    void on_btn_flashStackedBar_clicked();
    void on_btn_flashPercentBar_clicked();
    void on_btn_flashScatterChart_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *theModel;//数据模型
};
#endif // MAINWINDOW_H

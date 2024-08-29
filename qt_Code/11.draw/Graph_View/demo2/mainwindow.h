#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class QGraphicsScene;
class QLabel;
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    static const int ItemId = 1; //图形项自定义数据的key
    static const int ItemDesciption = 2;//图形项自定义数据的key
    int seqNum = 0; //用于图形项编号，每个图形项有一个编号
    //设置叠放顺序
    int frontZ = 0; //只增加
    int backZ = 0; //只减少

    QGraphicsScene *scene;//场景
    QLabel *labViewCord;
    QLabel *labSceneCord;
    QLabel *labItemCord;
    QLabel *labItemInfo;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_mouseMovePoint(QPoint point); //鼠标移动
    void on_mouseClicked(QPoint point); //鼠标单击
    void on_mouseDoubleClick(QPoint point); //鼠标双击
    void on_keyPress(QKeyEvent *event); //按键

private slots:
    void on_actItem_Rect_triggered();//矩形
    void on_actItem_Ellipse_triggered();//椭圆
    void on_actItem_Circle_triggered();//圆形
    void on_actItem_Triangle_triggered();//三角形
    void on_actItem_Polygon_triggered();//梯形
    void on_actItem_Line_triggered();//直线
    void on_actItem_Text_triggered();//文字
    void on_actItem_Pixmap_triggered();//图片

    void on_actZoomIn_triggered();//放大
    void on_actZoomOut_triggered();//缩小

    void on_actRotateLeft_triggered();//逆时针旋转
    void on_actRotateRight_triggered();//顺时针旋转
    void on_actRestore_triggered();//取消所有变换

    void on_actEdit_Front_triggered();//图形项前置
    void on_actEdit_Back_triggered();//图形项后置

    void on_actGroup_triggered();//组合
    void on_actGroupBreak_triggered();//打散

    void on_actEdit_Delete_triggered();//删除图形项

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

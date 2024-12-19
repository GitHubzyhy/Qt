#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPainterPath>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class RenderArea;
class QComboBox;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void shapeSelected(int index);//选择图形
    void operationChanged();//坐标轴操作

private:
    Ui::MainWindow *ui;

    void setupShapes();//准备好相应的图形

    static constexpr size_t NumTransformedAreas = 3;//编译期就确定

    RenderArea *originalRenderArea;//为了设置形状 哐哐
    RenderArea *transformedRenderAreas[NumTransformedAreas];//3个图形的旋转操作 框框

    // 下拉列表
    QComboBox *shapeComboBox;//设置形状的 组合框
    QComboBox *operationComboBoxes[NumTransformedAreas];//3个框框的 设置操作的 组合框

    QList<QPainterPath> shapes;//所有图像都放到这里 由setupShapes函数手写提供
};
#endif // MAINWINDOW_H

#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include<QPainterPath>
class RenderArea : public QWidget
{
    Q_OBJECT
public:
    enum Operation{NoTransformation,Rotate,Scale,Translate};//无变化，旋转，缩放，位移
    explicit RenderArea(QWidget *parent = nullptr);

    void setOperations(const QList<Operation> &operations);//获取operations的接口
    void setShape(const QPainterPath &shape);// 获取shape的接口
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    void drawCoordinates(QPainter &painter);//画坐标
    void drawOutLine(QPainter &painter);//画方格子
    void drawShape(QPainter &painter);//画形状
    void transformPainter(QPainter &painter);//改变

    QRect xBoundingRect;//x的外框矩形
    QRect yBoundingRect;//y的外框矩形

    QPainterPath shape;
    QList<Operation> operations;//保存叠加的操作
};

#endif // RENDERAREA_H

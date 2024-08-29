#ifndef BASEITEM_H
#define BASEITEM_H

#include <QObject>
#include <QImage>
#include <QRect>

class BaseItem : public QObject
{
    Q_OBJECT
public:
    QRect getRect();
    QImage &getImage();
protected:
    QImage image;
    QRect rect;///图形的大小
    explicit BaseItem(QObject *parent = nullptr);//不能被隐式调用
    virtual ~BaseItem();

    static const int RIGHT_EDGE = 300;//最右边边框的的位置
};

#endif // BASEITEM_H

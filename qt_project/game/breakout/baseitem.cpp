#include "baseitem.h"

QRect BaseItem::getRect()
{
    return rect;
}

QImage &BaseItem::getImage()
{
    return image;
}

BaseItem::BaseItem(QObject *parent)
    : QObject{parent} {}
BaseItem::~BaseItem()
{
    //作为良好的习惯而存在
}

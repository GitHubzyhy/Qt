#ifndef BRICK_H
#define BRICK_H

#include "baseitem.h"

class Brick : public BaseItem
{
    Q_OBJECT
public:
    Brick(int, int, QObject *parent = nullptr);

    //判断设置砖块是否应该被销毁
    bool isDestroyed();
    void setDestroyed(bool);
private:
    bool destroyed;
};

#endif // BRICK_H

#ifndef PADDLE_H
#define PADDLE_H

#include "baseitem.h"

class Paddle : public BaseItem
{
public:
    Paddle(QObject *parent = nullptr);

    void resetState();//把木板放到初始位置
    void move();//移动木板
    void setDx(int);//设置木板的方向

private:
    int dx;//木板的方向
    //木板的初始位置
    static const int INITIAL_X = 200;
    static const int INITIAL_Y = 360;
};

#endif // PADDLE_H

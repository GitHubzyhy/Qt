#include "paddle.h"

Paddle::Paddle(QObject *parent)
    : BaseItem{parent}
{
    image.load(":/images/paddle.png");

    rect = image.rect();
    resetState();
}
//把木板放到初始位置
void Paddle::resetState()
{
    setDx(0);
    rect.moveTo(INITIAL_X, INITIAL_Y);
}
//移动木板
void Paddle::move()
{
    //获取左上角的坐标
    int x = rect.x() + dx;
    int y = rect.y();

    //如果没有顶到边界就可以移动
    if ((x >= 0) && (x < RIGHT_EDGE - rect.width()))
        rect.moveTo(x, y);
}

void Paddle::setDx(int x)
{
    dx = x;
}

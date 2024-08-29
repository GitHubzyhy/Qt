#include "ball.h"

Ball::Ball(QObject *parent)
    : BaseItem{parent}
{
    image.load(":/images/ball.png");
    rect = image.rect(); //获取包裹该图形的rect
    resetState();
}
//把小球放到初始化位置
void Ball::resetState()
{
    xdir = 1, ydir = -1; //让其默认右上方向
    rect.moveTo(INITIAL_X, INITIAL_Y);
}
//撞到边框如何移动
void Ball::autoMove()
{
    //撞到边框就改变求的方向
    if (rect.left() == 0) xdir = 1;
    if (rect.right() == RIGHT_EDGE) xdir = -1;
    if (rect.top() == 0) ydir = 1;

    rect.translate(xdir, ydir);//相对于上一个位置该如何移动
}

void Ball::setXDir(int x)
{
    xdir = x;
}

void Ball::setYDir(int y)
{
    ydir = y;
}

int Ball::getXDir()
{
    return xdir;
}

int Ball::getYDir()
{
    return ydir;
}

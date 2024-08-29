#ifndef BALL_H
#define BALL_H

#include "baseitem.h"

class Ball : public BaseItem
{
public:
    explicit Ball(QObject *parent = nullptr);
public:
    void resetState();//把小球放到初始化位置
    void autoMove();//撞到边框如何移动
    //设置获取坐标
    void setXDir(int);
    void setYDir(int);
    int getXDir();
    int getYDir();
private:
    //球的前进的方向
    int xdir;
    int ydir;
    //球初始位置
    static const int INITIAL_X = 230;
    static const int INITIAL_Y = 355;
};

#endif // BALL_H

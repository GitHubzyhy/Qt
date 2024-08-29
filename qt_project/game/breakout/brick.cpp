#include "brick.h"

Brick::Brick(int x, int y, QObject *parent)
{
    destroyed = false;//默认没有被销毁
    image.load(":/images/brick.png");
    rect = image.rect();
    rect.translate(x, y);
}

bool Brick::isDestroyed()
{
    return destroyed;
}

void Brick::setDestroyed(bool b)
{
    destroyed = b;
}

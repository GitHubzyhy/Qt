#ifndef SNACKWIDGET_H
#define SNACKWIDGET_H

#include <QWidget>

class SnackWidget : public QWidget
{
    Q_OBJECT

public:
    SnackWidget(QWidget *parent = nullptr);
    ~SnackWidget();

    //枚举的操作
    enum moveDirection { left, right, up, down };
protected:
    void timerEvent(QTimerEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private:
    QImage dot; //身体的一节
    QImage head;//蛇头
    QImage apple;//蛇尾
    moveDirection heading;
    static const int B_WIDTH = 300;//宽
    static const int B_HEIGHT = 300;//高
    static const int DOT_SIZE = 10; //身体一节的大小，10*10
    static const int ALL_DOTS = B_WIDTH *B_HEIGHT / (DOT_SIZE *DOT_SIZE);//划分成900个格子

    int timerId;//通过id找到计时器
    int length_snake;//蛇的长度
    //苹果的位置
    int apple_x;
    int apple_y;
    bool game_playing;//游戏的状态
    //蛇的位置蛇最多有ALL_DOTS节数
    int x[ALL_DOTS];
    int y[ALL_DOTS];

    void initGame();//初始化
    void locateApple();//初始化苹果的位置

    void move();//蛇的移动
    void checkApple();//判断是否咬到苹果了
    void checkCollision();//判断咬到自己/撞到边界
    void gameOver(QPainter &);
};
#endif // SNACKWIDGET_H

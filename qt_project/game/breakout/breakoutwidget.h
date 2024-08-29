#ifndef BREAKOUTWIDGET_H
#define BREAKOUTWIDGET_H

#include <QWidget>

class Ball;
class Paddle;
class Brick;
class BreakOutWidget : public QWidget
{
    Q_OBJECT

public:
    BreakOutWidget(QWidget *parent = nullptr);
    ~BreakOutWidget();

    void startGame();//开始游戏
    void pauseGame();//暂停游戏
    void stopGame();//失败
    void victory();//通关
    void finishGame(QPainter *, QString);//完成游戏

    void checkCollision();//判断碰撞
    void checkPaddleCollision();//判断木板和球的碰撞
    void checkBricksCollision();//判断球和砖块的碰撞
protected:
    void timerEvent(QTimerEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;//改变木板位置
    void keyReleaseEvent(QKeyEvent *event) override;//让木板停下来
private:
    int timerId;//控制刷新
    static const int N_OF_BRICKS = 30;//初始化30个砖头
    static const int DELAY = 10;//刷新周期，1s100次
    static const int BOTTOM_EDGE = 400;//判断小球是否掉下去了

    Ball *ball;
    Paddle *paddle;
    Brick *bricks[N_OF_BRICKS];//放5行6列

    //游戏状态
    bool gameOver;
    bool gameWon;
    bool gameStarted;
    bool paused;

    //掉下的砖块=30代表游戏结束
    unsigned brokenBricks;
};
#endif // BREAKOUTWIDGET_H

#include "breakoutwidget.h"
#include "ball.h"
#include "paddle.h"
#include "brick.h"
#include <QPainter>
#include <QApplication>
#include <QKeyEvent>
#include <QFontMetrics>

BreakOutWidget::BreakOutWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowIcon(QIcon(":/images/ball.png"));
    setWindowTitle("打砖块");

    setStyleSheet("background-color:gray;");
    setFixedSize(300, 400);

    ball = new Ball(this);
    paddle = new Paddle(this);

    //初始化砖块 5行6列
    const int paddle_w = paddle->getRect().width();
    const int paddle_h = paddle->getRect().height();
    for (int i = 0, k = 0; i < 5; ++i)
        for (int j = 0; j < 6; ++j)
            bricks[k++] = new Brick(30 + j *paddle_w, 50 + i *paddle_h, this);

    gameOver = false;
    gameWon = false;
    gameStarted = false;
    paused = true;
}

BreakOutWidget::~BreakOutWidget() {}

//开始游戏
void BreakOutWidget::startGame()
{
    if (!gameStarted)
    {
        setStyleSheet("background-color:gray;");
        //状态重置
        ball->resetState();
        paddle->resetState();
        for (int i = 0; i < N_OF_BRICKS; ++i)
            bricks[i]->setDestroyed(false);

        gameOver = false;
        gameWon = false;
        gameStarted = true;
        timerId = startTimer(DELAY);//开启定时任务
        brokenBricks = 0;//打落的砖块数量归零
    }
}
//暂停游戏
void BreakOutWidget::pauseGame()
{
    if (paused) //已经是暂停状态
    {
        paused = false;
        killTimer(timerId);//停止定时
    }
    else
    {
        paused = true;
        timerId = startTimer(DELAY);//开启定时任务
    }
}
//失败
void BreakOutWidget::stopGame()
{
    gameOver = true;
    gameStarted = false;
    killTimer(timerId);
}
//通关
void BreakOutWidget::victory()
{
    gameWon = true;
    gameStarted = false;
    killTimer(timerId);
}
//完成游戏
void BreakOutWidget::finishGame(QPainter *painter, QString message)
{
    setStyleSheet("background-color:white;");
    QFont font("Courier", 15);
    QFontMetrics fm(font);
    int textWidth = fm.horizontalAdvance(message);
    int hightWidth = fm.height();

    painter->setFont(font);
    int h = height();
    int w = width();

    painter->translate(QPoint(w / 2, h / 2));
    painter->drawText(-textWidth / 2, -hightWidth / 2, message);
}
//判断碰撞
void BreakOutWidget::checkCollision()
{
    //球掉下去了
    if (ball->getRect().bottom() > BOTTOM_EDGE)
    {
        stopGame();
        return;
    }
    //开始检测判断碰撞
    checkPaddleCollision();
    checkBricksCollision();
    if (brokenBricks >= N_OF_BRICKS) victory();
}
//判断木板和球的碰撞
void BreakOutWidget::checkPaddleCollision()
{
    if (ball->getRect().intersects(paddle->getRect()))
    {
        int paddleLPos = paddle->getRect().left();//木板左边的位置
        int ballPos = ball->getRect().left(); //球左边的位置

        int oneFifthPaddle = paddle->getRect().width() / 5; //木板长度的1/5
        int twoFifthPaddlePos = paddleLPos + 2 * oneFifthPaddle;
        int threeFifthPaddlePos = paddleLPos + 3 * oneFifthPaddle;
        //开始决定球碰到木板往哪个方向弹
        if (ballPos < twoFifthPaddlePos)
            ball->setXDir(-1);//向左弹
        else if (ballPos >= twoFifthPaddlePos
                 && ballPos < threeFifthPaddlePos)
            ball->setXDir(0);//向上弹
        else
            ball->setXDir(1);//向右弹

        ball->setYDir(-1);//总是让球向上运动
    }
}
//判断球和砖块的碰撞
void BreakOutWidget::checkBricksCollision()
{
    for (int i = 0; i < N_OF_BRICKS; ++i)
    {
        //以及被摧毁的砖块就不管了
        if (bricks[i]->isDestroyed()) continue;
        //判断是否发生相交(碰撞)了
        if (ball->getRect().intersects(bricks[i]->getRect()))
        {
            int ballLeft = ball->getRect().left();
            int ballHeight = ball->getRect().height();
            int ballWidth = ball->getRect().width();
            int ballTop = ball->getRect().top();

            //碰撞的4个点
            QPoint pointRight(ballLeft + ballWidth, ballTop);
            QPoint pointLeft(ballLeft, ballTop);
            QPoint pointTop(ballLeft, ballTop);
            QPoint pointBottom(ballLeft, ballTop + ballHeight);
            //往哪里弹 碰到右边往左边弹 同理...
            if (bricks[i]->getRect().contains(pointRight)) ball->setXDir(-1);
            if (bricks[i]->getRect().contains(pointLeft)) ball->setXDir(1);
            if (bricks[i]->getRect().contains(pointTop)) ball->setYDir(1);
            if (bricks[i]->getRect().contains(pointBottom)) ball->setYDir(-1);

            bricks[i]->setDestroyed(true);//销毁状态
            brokenBricks++;//得分++
            break;
        }
    }
}

void BreakOutWidget::timerEvent(QTimerEvent *event)
{
    ball->autoMove();
    paddle->move();

    checkCollision();//判断球和砖块的碰撞
    repaint();//重新绘制
}

void BreakOutWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (gameOver)
        finishGame(&painter, "Game Over");
    else if (gameWon)
        finishGame(&painter, "Victory");
    else
    {
        //画球和移动的木板
        painter.drawImage(ball->getRect(), ball->getImage());
        painter.drawImage(paddle->getRect(), paddle->getImage());
        //画砖块
        for (int i = 0; i < N_OF_BRICKS ; ++i)
            if (!bricks[i]->isDestroyed()) //砖头状态没有被销毁
                painter.drawImage(bricks[i]->getRect(), bricks[i]->getImage());
    }
}
//改变木板位置
void BreakOutWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Left:
            paddle->setDx(-1);
            break;
        case Qt::Key_Right:
            paddle->setDx(1);
            break;
        case Qt::Key_P:
            pauseGame();
            break;
        case Qt::Key_Space:
            startGame();
            break;
        case Qt::Key_Escape:
            qApp->exit();
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}
//让木板停下来
void BreakOutWidget::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Left:
            ;
        case Qt::Key_Right:
            paddle->setDx(0);
            break;
        default:
            QWidget::keyReleaseEvent(event);
    }
}

#include "snackwidget.h"
#include <QRandomGenerator>//随机数
#include <QPainter>
#include <QKeyEvent>

SnackWidget::SnackWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowIcon(QIcon(":/images/apple.png"));
    setWindowTitle("贪吃蛇");

    //加载图片
    dot.load(":/images/dot.png"); //身体的一节
    head.load(":/images/head.png");
    apple.load(":/images/apple.png");

    setFixedSize(B_WIDTH, B_HEIGHT);

    initGame();
}

SnackWidget::~SnackWidget() {}

void SnackWidget::timerEvent(QTimerEvent *event)
{
    if (game_playing)//游戏正常运行的情况下
    {
        checkApple();//判断是否咬到苹果
        move();
        checkCollision();//判断是否撞到边界
    }
    repaint();//立即重写绘制
}

void SnackWidget::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    switch (key)
    {
        case Qt::Key_Left:
            if (heading != right) heading = left;
            break;
        case Qt::Key_Right:
            if (heading != left) heading = right;
            break;
        case Qt::Key_Up:
            if (heading != down) heading = up;
            break;
        case Qt::Key_Down:
            if (heading != up) heading = down;
            break;
        default:
            break;
    }

    //游戏结束的情况下按空格可以重新开始游戏
    if (key == Qt::Key_Space && game_playing == false)
        initGame();

    QWidget::keyPressEvent(event);
}

void SnackWidget::paintEvent(QPaintEvent *event)
{
    QPainter qp(this);//在此绘图设备上绘图
    if (game_playing)//游戏正常运行中
    {
        qp.drawImage(apple_x, apple_y, apple);//画苹果

        for (int i = 0; i < length_snake; i++)
        {
            if (i == 0)//画头
                qp.drawImage(x[i], y[i], head);
            else//画尾巴
                qp.drawImage(x[i], y[i], dot);
        }
    }
    else
        gameOver(qp);
}
//初始化
void SnackWidget::initGame()
{
    setStyleSheet("background-color:black");//背景为黑色
    heading = right; //头的位置向右
    length_snake = 3; //3节
    game_playing = true; //游戏是启动的状态

    //初始化蛇的位置 30*30个格子，一个格子是10*10
    for (int i = 0; i < length_snake; ++i)
    {
        x[i] = 30 - i *DOT_SIZE;
        y[i] = 30; //高度不变
    }
    locateApple();//初始化苹果的位置
    timerId = startTimer(100);//返回定时器标识符，为了后续中止定时器
}
//初始化苹果的位置
void SnackWidget::locateApple()
{
    int randomInt = QRandomGenerator::global()->bounded(B_WIDTH / DOT_SIZE);
    apple_x = randomInt *DOT_SIZE;
    randomInt = QRandomGenerator::global()->bounded(B_HEIGHT / DOT_SIZE);
    apple_y = randomInt *DOT_SIZE;
}
//蛇的移动
void SnackWidget::move()
{
    //尾巴的坐标
    for (int i = length_snake - 1; i > 0; --i)
    {
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }
    //头部的坐标
    switch (heading)
    {
        case left:
            x[0] -= DOT_SIZE;
            break;
        case right:
            x[0] += DOT_SIZE;
            break;
        case up:
            y[0] -= DOT_SIZE;
            break;
        case down:
            y[0] += DOT_SIZE;
            break;
    }
}
//判断是否咬到苹果了
void SnackWidget::checkApple()
{
    if ((x[0] == apple_x) && (y[0] == apple_y))
    {
        ++length_snake;
        locateApple();
    }
}
//判断咬到自己/撞到边界
void SnackWidget::checkCollision()
{
    //判断是否咬到自己
    if (length_snake > 4) //这样才能咬到自己
        for (int i = length_snake - 1; i > 0; --i)
            if (x[0] == x[i] && y[0] == y[i])
                game_playing = false;
    //判断是否撞到边界
    if (x[0] >= B_WIDTH || x[0] < 0 || y[0] >= B_HEIGHT || y[0] < 0)
        game_playing = false;

    if (game_playing == false)
        killTimer(timerId);//杀死具有定时器标识符 id 的定时器
}
//游戏结束
void SnackWidget::gameOver(QPainter &qp)
{
    setStyleSheet("background-color:white;");
    QString message = "Game Over!!!";
    QFont font("Courier", 15);//字体，字体大小
    QFontMetrics fm(font);//计算字体的高度宽度
    int textWidth = fm.horizontalAdvance(message);
    int textHeight = fm.height();

    qp.setFont(font);//设置画家字体
    int h = height();
    int w = width();

    qp.translate(w / 2, h / 2);
    qp.drawText(-textWidth / 2, -textHeight / 2, message);
}

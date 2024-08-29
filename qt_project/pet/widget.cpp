#include "widget.h"
#include <QPainter>
#include <QTimer>
#include <QPixmap>
#include <QMenu>
#include <QCursor>
#include <QMetaEnum>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      timer(new QTimer(this)),
      menu(new QMenu(this))
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);//去除窗口边框
    setAttribute(Qt::WA_TranslucentBackground, true);

    installEventFilter(new DragFliter);

    connect(timer, &QTimer::timeout, this, [this]()
    {
        static int index = 0; //记录显示动作图片的当前索引(持久性)
        QList<QUrl> paths = action_map.value(cur_role_act);
        cur_role_pix = paths[index++ % paths.size()];

        update();
    });

    initMenu();//初始化菜单
    loadRoleActRes();//加载资源
    showActAnimation(RoleAct::Swing);//显示动作
}

Widget::~Widget() {}
//显示动作
void Widget::showActAnimation(RoleAct k)
{
    timer->stop();
    this->cur_role_act = k;
    timer->start(90);
}

//菜单被触发的槽
void Widget::onMenuTriggered(QAction *action)
{
    QMetaEnum me = QMetaEnum::fromType<RoleAct>();

    bool ok;
    int k = me.keyToValue(action->text().toStdString().c_str(), &ok);
    if (!ok)
        return;

    showActAnimation(static_cast<RoleAct>(k));//显示动作
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);//在当前窗口绘图

    QPixmap pix;
    pix.load(cur_role_pix.toLocalFile());//将url转换成本地路径

    painter.drawPixmap(0, 0, pix); //将图片绘制在左上角
}
//加载资源
void Widget::loadRoleActRes()
{
    auto addRes = [this](RoleAct k, QString path, int count) //动作,路径,图片个数
    {
        QList<QUrl> paths;
        char buf[260];//路径最大长度为260位
        for (int i = 0; i < count; ++i)
        {
            memset(buf, 0, sizeof(buf)); //初始化为0
            sprintf_s(buf, path.toStdString().c_str(), i);//将整数i插入到字符串path中，并将结果存储在字符数组buf中
            paths << QUrl::fromLocalFile(buf);
        }
        action_map.insert(k, paths); //完成动作和图片的映射关系
    };

    //开始加载图片
    addRes(RoleAct::SayHello, ":/sayHello/img/sayHello/sayHello_%d.png", 28);
    addRes(RoleAct::Sleep, ":/sleep/img/sleep/sleep_%d.png", 25);
    addRes(RoleAct::Swing, ":/swing/img/swing/swing_%d.png", 32);
}
//初始化菜单
void Widget::initMenu()
{
    menu->addAction("SayHello");
    menu->addAction("Sleep");
    menu->addAction("Swing");

    QAction *act = new QAction("hide");
    connect(act, &QAction::triggered, this, [this]
    {
        this->hide();
    });

    menu->addAction(act);
    connect(menu, &QMenu::triggered, this, &Widget::onMenuTriggered);
}
//右键菜单
void Widget::contextMenuEvent(QContextMenuEvent *event)
{
    menu->popup(QCursor::pos());//非阻塞
    // 调用accept 表示，这个事件我已经处理，不需要向上传递了
    event->accept();
}

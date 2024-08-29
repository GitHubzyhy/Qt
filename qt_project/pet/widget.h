#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMap>
#include <QUrl>
#include <QEvent>
#include <QMouseEvent>

namespace Act
{
    Q_NAMESPACE//标识命名空间

    enum RoleAct
    {
        Swing,
        Sleep,
        SayHello
    };
    Q_ENUM_NS(RoleAct)//注册给元对象系统就可以实现字符串和枚举相互转换
}

using namespace Act;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void showActAnimation(RoleAct k);//显示动作
public slots:
    void onMenuTriggered(QAction *action);//菜单被触发的槽
    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void contextMenuEvent(QContextMenuEvent *event) override;

private:
    void loadRoleActRes();//加载资源
    void initMenu();//初始化菜单

private:
    QMap< RoleAct, QList<QUrl> > action_map;//动作和图片路径对应
    QTimer *timer;
    RoleAct cur_role_act;//当前动作
    QUrl cur_role_pix;//当前动作对应的图片
    QMenu *menu;
};

class DragFliter: public QObject
{
    // QObject interface
public:
    virtual bool eventFilter(QObject *watched, QEvent *event) override
    {
        auto w = dynamic_cast<QWidget *>(watched); //转换成窗口类型
        if (!w) return false;//返回false这个事件就会继续向下传递
        if (event->type() == QEvent::MouseButtonPress)
        {
            auto e = dynamic_cast<QMouseEvent *>(event);//父类向子类转换
            if (e) //转换成功
                pos = e->position().toPoint();
        }
        else if (event->type() == QEvent::MouseMove)
        {
            auto e = dynamic_cast<QMouseEvent *>(event);
            if (e->buttons()&Qt::LeftButton)
                w->move(e->globalPosition().toPoint() - pos); //实现拖动
        }
        return QObject::eventFilter(watched, event);//调用父类让他去处理其他事件
    }
private:
    QPoint pos;
};

#endif // WIDGET_H

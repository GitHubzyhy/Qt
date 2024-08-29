#ifndef DRAGABLEFORM_H
#define DRAGABLEFORM_H

#include <QFrame>

namespace Ui
{
    class DragableForm;
}

class DragableForm : public QFrame
{
    Q_OBJECT

public:
    explicit DragableForm(QWidget *parent = nullptr);
    ~DragableForm();

private:
    Ui::DragableForm *ui;

    // QWidget interface
protected:
    /*  确定要拖拽的数据、设置拖拽的图标和传输数据的类型等
        。通常，在这里设置拖拽的数据，创建一个QDrag对象，并调用QDrag::exec()来启动拖拽操作。*/
    void mousePressEvent(QMouseEvent *event);

    /*  这个事件处理函数将在有拖动进入该小部件时被调用，你可以在这里进行一些准备工作或判断，
        例如检查拖放的数据类型是否合法，然后调用 event->acceptProposedAction()
        表示接受拖放动作。*/
    void dragEnterEvent(QDragEnterEvent *event);

    //这个事件处理函数将在拖放操作完成（即用户释放鼠标）时被调用，你可以在这里获取拖放的数据并进行相应的处理。
    void dropEvent(QDropEvent *event);
};

#endif // DRAGABLEFORM_H

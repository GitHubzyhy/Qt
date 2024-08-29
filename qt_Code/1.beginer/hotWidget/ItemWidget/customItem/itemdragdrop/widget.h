#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class QAbstractItemView;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_radioButtonInter_clicked(bool checked);
    void on_radioButtonOuter_clicked(bool checked);

private:
    Ui::Widget *ui;

    //设置 QAbstractItemView 派生类的跨界拖拽功能
    //对列表控件、树形控件、表格控件通用，C++多态性
    void SetOuterDragDrop( QAbstractItemView *view );
};
#endif // WIDGET_H

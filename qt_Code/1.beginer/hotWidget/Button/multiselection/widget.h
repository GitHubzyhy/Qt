#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //检查兴趣爱好，同步更新三态复选框的状态
    void CheckHobbies();

private slots:
    void on_pushButton_clicked();//显示弹窗

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

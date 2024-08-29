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

private slots:
    void on_pushButton_clicked();

    void on_btnFixed_clicked();

private:
    Ui::Widget *ui;
    //第二个示范窗口，全部放置 QLineEdit
    QWidget *m_pWidget;
    //通过代码构造第二个示范窗口
    void CreateWidget();
};
#endif // WIDGET_H

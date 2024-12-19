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
    void on_btnOpen_clicked();//打开html

    void on_textBrowser_backwardAvailable(bool arg1);//根据能否后退，设置 "后退" 按钮可用状态
    void on_textBrowser_forwardAvailable(bool arg1);//根据能否前进，设置 "前进" 按钮可用状态
    void on_textBrowser_textChanged();//当 QTextBrowser 控件内容变化时，QPlainTextEdit 跟着变化

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

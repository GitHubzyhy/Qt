#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class QTextCharFormat;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnBold_clicked(bool checked);//粗体
    void on_btnItalic_clicked(bool checked);//斜体
    void on_btnUnderline_clicked(bool checked);//下划线
    void on_btnColor_clicked();//文字前景色设置
    void on_btnBGColor_clicked();//文字背景色设置
    void on_FontSize_editingFinished();//字号修改好了，设置选中文本的字号
    void on_textEdit_currentCharFormatChanged(const QTextCharFormat &format);//根据光标位置或选中文本感知字体格式
    void on_textEdit_textChanged();//打印

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

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
    void on_pushButtonBrowseSrc_clicked();//打开配置文件

    void on_pushButtonLoad_clicked();//加载配置

    void on_pushButtonBrowseDst_clicked();//保存文件名

    void on_pushButtonSave_clicked();//保存配置

private:
    Ui::Widget *ui;
    //分析一行配置文本，设置到对应的控件里
    void AnalyzeOneLine(const QByteArray &baLine);
};
#endif // WIDGET_H

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

    //初始化填充
    void InitTCPLinks();
    //更新树形控件的显示
    void UpdateTreeShow();

private slots:
    void on_pushButtonAddTCP_clicked();//添加TCP连接
    void on_pushButtonDelIP_clicked();//删除匹配IP连接
    void on_pushButtonDelPort_clicked();//删除匹配端口连接
    void on_pushButtonFindBelow1024_clicked();//查找1024以下小端口连接
    void on_pushButtonPlus1024_clicked();//给小端口增加1024

private:
    Ui::Widget *ui;

    //保存IP和端口信息
    QMultiMap<QString, int> m_tcplinks;
};
#endif // WIDGET_H

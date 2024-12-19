#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QElapsedTimer>
#include <QLocale>

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
    void on_pushButtonInsert_clicked();//添加元素
    void on_pushButtonFind_clicked();//随机访问

private:
    Ui::Widget *ui;

    //容器对象
    QMap<int, int> m_map;
    QHash<int, int> m_hash;
    QSet<int> m_set;

    QElapsedTimer m_calcTimer;//耗费计时器
    QLocale m_locale;//本地化对象，用于打印逗号分隔的数字
};
#endif // WIDGET_H

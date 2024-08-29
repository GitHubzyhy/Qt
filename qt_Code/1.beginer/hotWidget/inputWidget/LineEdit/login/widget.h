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
    void on_pushButtonLogin_clicked();
    void on_pushButtonExit_clicked();

private:
    Ui::Widget *ui;

    QString m_strUser;//用户名
    QByteArray m_passwordHash;//不能明文保存密码，存储密码 hash 值
};
#endif // WIDGET_H

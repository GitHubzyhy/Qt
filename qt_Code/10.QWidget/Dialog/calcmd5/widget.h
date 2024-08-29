#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QErrorMessage>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class QFile;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButtonBrowser_clicked();//浏览要打开的文件
    void on_pushButtonCalcMD5_clicked();//计算文件 MD5

private:
    Ui::Widget *ui;

    QErrorMessage m_dlgErrorMsg;//错误消息框
    QString m_strFileName;//文件名
    //计算文件对象 MD5 值
    QByteArray CalcFileMD5( QFile &fileIn, qint64 nFileSize );
};
#endif // WIDGET_H

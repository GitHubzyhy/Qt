#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class TabPreview;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

signals://文件名变化时触发该信号
    void fileNameChanged(const QString &fileName);

private slots://选择文件的槽函数
    void on_pushButtonSelectFile_clicked();

private:
    Ui::Widget *ui;

    TabPreview *m_pTabPreview;//自定义第三个标签页面
    QString m_strFileName;//文件全名
    QFileInfo m_fileInfo;//文件信息查看对象

};
#endif // WIDGET_H

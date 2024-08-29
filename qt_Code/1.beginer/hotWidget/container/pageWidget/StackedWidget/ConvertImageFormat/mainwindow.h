#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class QLabel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //初始化控件函数
    void InitControls();

private slots://打开图片和转换图片格式的槽函数
    void on_pushButtonOpen_clicked();

    void on_pushButtonConvert_clicked();

private:
    Ui::MainWindow *ui;

    QLabel *m_pLabelPreview;//图片预览标签
    QString m_strImageName; //图片文件名
    QImage m_image; //加载图片对象
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "weatherdata.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class QNetworkAccessManager;//协助网络操作
class QNetworkReply;//网络请求的响应
class QLabel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    // 获取到网络响应调用的槽函数
    void onReplied(QNetworkReply *reply);
    // 获取天气数据(发送请求) 参数是城市名称
    void getWeatherInfo(QString cityName);
    //解析天气数据
    void parseJson(QByteArray &byteArray);
    //更新ui界面
    void updateUI();
    // 绘制高低温曲线
    void paintHighCurve();
    void paintLowCurve();
private:
    Ui::MainWindow *ui;

    QMenu *mExitMenu;//右键退出菜单
    QAction *mExitAct;//菜单项

    QPoint mOffset; // 窗口移动时, 鼠标与窗口左上角的偏移

    QNetworkAccessManager *mNetAccessManager;

    Today mToday;
    Day mDay[6];//6天的数据(包括了部分今天的数据)

    // 星期和日期
    QList<QLabel *> mWeekList;
    QList<QLabel *> mDateList;

    // 天气和天气图标
    QList<QLabel *> mTypeList;
    QList<QLabel *> mTypeIconList;

    // 天气指数
    QList<QLabel *> mAqiList;

    // 风向和风力
    QList<QLabel *> mFxList;
    QList<QLabel *> mFlList;

    QMap<QString, QString> mTypeMap;//图标的中英文转换

    // QWidget interface
protected:
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
private slots:
    void on_btnSearch_clicked();//搜索

    // QObject interface
public:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
};
#endif // MAINWINDOW_H

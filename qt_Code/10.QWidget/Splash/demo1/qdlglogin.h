#ifndef QDLGLOGIN_H
#define QDLGLOGIN_H

#include <QDialog>

namespace Ui
{
    class QDlgLogin;
}

class QDlgLogin : public QDialog
{
    Q_OBJECT
private:
    bool m_moving = false; //表示窗口是否在鼠标操作下移动
    QPoint m_lastPos;//上一次鼠标位置
    QString m_user = "user"; //初始化用户名
    QString m_pswd = "12345"; ///初始化密码，未命名的

    int m_tryCount = 0; //试错次数
    void readSetting();//读取设置，注册表
    void writeSettings();//写入设置，注册表
    QString encrypt(const QString &str);//字符串加密

public:
    explicit QDlgLogin(QWidget *parent = nullptr);
    ~QDlgLogin();

private slots:
    void on_btn_Ok_clicked();

private:
    Ui::QDlgLogin *ui;

    // QWidget interface
protected://因为设置的无边框，所以要自己设置窗口拖动
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // QDLGLOGIN_H

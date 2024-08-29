#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QMessageBox>

void loadCss(Page_Login &m_dlgLogin)
{
    QFile fileIn;
    fileIn.setFileName(":/stuqss.css");
    if (!fileIn.open(QIODevice::ReadOnly)) //选择只读打开
    {
        QMessageBox::warning(nullptr, "打开错误"
                             , "打开文件错误：" + fileIn.errorString());
        return; //不处理文件
    }

    QString strQss = fileIn.readAll();

    m_dlgLogin.setStyleSheet(strQss); //把样式给主界面
    fileIn.close();
    m_dlgLogin.show();//进入登录界面 非模态
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Page_Login m_dlgLogin;
    loadCss(m_dlgLogin);

    //调用connect函数进行连接
    QObject::connect(&m_dlgLogin, &Page_Login::SendLoginSuccess, &w, [&]
    {
        m_dlgLogin.close();
        w.show();
    });

    return a.exec();
}

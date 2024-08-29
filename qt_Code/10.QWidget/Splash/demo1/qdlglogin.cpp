#include "qdlglogin.h"
#include "ui_qdlglogin.h"
#include <QSettings>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QMouseEvent>

void QDlgLogin::readSetting()
{
    //读取存储的用户名和密码，密码是经过加密的
    QString organization = "zyhDir"; //注册表
    QString appName = "splashDemo";
    QSettings settings(organization, appName); //打开一个QSettings对象

    bool saved = settings.value("saved", false).toBool(); //读取saved键，并判断返回是否存在saved键，缺省值为flase
    m_user = settings.value("Username", "user").toString(); //读取Username键的值，缺省值为user
    QString defaultPSWD = encrypt("12345"); //默认的密码（加密过的）
    m_pswd = settings.value("PSWD", defaultPSWD).toString(); //读取PSWD键的值，缺省值为defaultPSWD

    if(saved) //如果saved有键，就将Username显示在editUser控件中
        ui->editUser->setText(m_user);

    ui->chkBoxSave->setChecked(saved); //设置当前是否保存用户名
}

void QDlgLogin::writeSettings()
{
    //保存用户名密码等
    QSettings settings("zyhDir", "splashDemo"); //打开一个QSettings对象

    settings.setValue("Username", m_user); //将m_user设置为Username键的值
    settings.setValue("PSWD", m_pswd); //将m_pswd设置为PSWD键的值
    settings.setValue("saved", ui->chkBoxSave->isChecked()); //将chkBoxSave的选择结果设置为saved键的值
}

QString QDlgLogin::encrypt(const QString &str)
{
    //将传入进来的密码字符串转换为字节数组，因为加密算法需要字节对象
    QByteArray btArray;
    btArray.append(str.toUtf8());

    //指定MD5加密算法的QCryptographicHash对象
    QCryptographicHash hash(QCryptographicHash::Md5);//MD5加密算法
    hash.addData(btArray); //将btArray作为参数加密
    QByteArray resultArray = hash.result(); //得到hash加密后的结果

    QString md5 = resultArray.toHex(); //将字节数组内容转换为字符串
    return md5; //返回加密后的密码

}

QDlgLogin::QDlgLogin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QDlgLogin)
{
    ui->setupUi(this);
    ui->editPSWD->setEchoMode(QLineEdit::Password);//设置密码编辑框输入模式为密码输入模式
    setAttribute(Qt::WA_DeleteOnClose);//当前窗体关闭时窗体对象删除
    setWindowFlags(Qt::SplashScreen); //当前窗体设置为SplashScreen格式,无边框，在Windows任务栏不显示标题
    // setWindowFlags(Qt::FramelessWindowHint);
    readSetting(); //读取存储的用户名和密码
}

QDlgLogin::~QDlgLogin()
{
    delete ui;
}

void QDlgLogin::on_btn_Ok_clicked()
{
    QString user = ui->editUser->text().trimmed(); //得到输入的用户名
    QString pswd = ui->editPSWD->text().trimmed(); //得到输入的密码
    QString encrptPSWD = encrypt(pswd); //将输入的密码进行MD5加密

    //如果账户名和密码都正确
    if((user == m_user) && (encrptPSWD == m_pswd))//两个加密的密码进行对比是否相等
    {
        writeSettings();//将用户名和密码写入注册表
        this->accept();//对话框关闭
    }
    else//如果输入错误
    {
        m_tryCount++;

        if(m_tryCount > 3) //错误次数大于3次，直接退出
        {
            QMessageBox::critical(this, QStringLiteral("错误"),
                                  QStringLiteral("输入错误次数过多"));
            this->reject(); //窗体退出
        }
        else//错误次数小于等于3次，只提示不退出
            QMessageBox::critical(this, QStringLiteral("错误提示"),
                                  QStringLiteral("用户名或密码错误"));
    }

}

void QDlgLogin::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_moving = true; //当前窗口被鼠标单击选中
        m_lastPos = event-> globalPosition().toPoint() - geometry().topLeft(); //记录下鼠标相对于当前窗口的位置
    }

    return QDialog::mouseMoveEvent(event);

}

void QDlgLogin::mouseMoveEvent(QMouseEvent *event)
{
    //鼠标移动事件
    //当前窗口被选中&&鼠标左键被按下&&鼠标移动的位置大于鼠标一开始选中的位置
    if(m_moving && (event->buttons() & Qt::LeftButton) &&
        (event->globalPosition().toPoint() - m_lastPos).manhattanLength() > QApplication::startDragDistance())
    {
        //如果当前鼠标位置与上一次保存的位置之间的曼哈顿距离大于应用程序定义的拖动开始的距离阈值，那么就认为拖动已经开始了
        move(event->globalPosition().toPoint() - m_lastPos); //窗口移动到参数所给的位置
        m_lastPos = event->globalPosition().toPoint() - pos(); //更新移动后鼠标相对于当前窗口的位置
    }

    return QDialog::mouseMoveEvent(event);

}

void QDlgLogin::mouseReleaseEvent(QMouseEvent *event)
{
    m_moving = false; //当前鼠标没有按下并且不移动
}

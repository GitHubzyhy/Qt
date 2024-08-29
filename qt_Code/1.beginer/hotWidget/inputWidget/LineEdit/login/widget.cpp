#include "widget.h"
#include "./ui_widget.h"
#include <QMessageBox>
#include <QCryptographicHash>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->lineEditPassword->setEchoMode(QLineEdit::PasswordEchoOnEdit);//设置密码框的显示模式

    //开始对输入做限制
    QRegularExpression rx("^[1-9]{8}$");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->lineEditPassword->setValidator(validator);//将验证器设置给lineEdit
}

Widget::~Widget()
{
    delete ui;
}
//登录按钮
void Widget::on_pushButtonLogin_clicked()
{
    //判断用户名密码是否为空
    if (ui->lineEditUser->text().isEmpty()
        || ui->lineEditPassword->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, tr("警告信息"), tr("用户名或密码为空，不能登录。"));
        return;
    }

    m_strUser = ui->lineEditUser->text(); //用户名
    m_passwordHash = QCryptographicHash::hash(ui->lineEditPassword->text().toUtf8(),
                     QCryptographicHash::Sha3_256 );
    //构造消息
    //添加用户名
    QString strMsg = tr("用户名: ") + m_strUser + tr("\r\n") + tr("密码 Hash：");
    //把每个 Hash 字节转成一对十六进制字符显示
    // 256 bit 对应 32 字节，变成 64 个十六进制字符打印
    strMsg += m_passwordHash.toHex();
    qDebug() << strMsg;
    //弹窗显示，注意：实际应用中会将用户名和密码 Hash 与数据库或配置文件里的做比较，而不是弹窗
    QMessageBox::information(this, tr("用户信息"), strMsg);
}

void Widget::on_pushButtonExit_clicked()
{
    close();
}

#include "widget.h"
#include "./ui_widget.h"
#include <QCommandLinkButton>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->checkBoxTristate->setTristate(true);//设置三态工作模式

    //复选框的信号槽连接
    QObjectList childCk = ui->groupBox->children(); //获取子类列表
    int ckLen = childCk.length();
    for (int i = 1; i < ckLen; ++i)//0号是布局
    {
        auto ckBox = static_cast<QCheckBox *> (childCk[i]);
        connect(ckBox, &QCheckBox::toggled,
                this, [this, ckBox](bool checked)
        {
            if (checked)
                qDebug() << ckBox->text();
            CheckHobbies(); //更新三态复选框
        });
    }

    //命令连接按钮的信号槽连接
    connect(ui->commandLinkButtonFolder, &QCommandLinkButton::clicked,
            this, []
    {
        QDesktopServices::openUrl( QUrl("file:///D:/") );
    });
    connect(ui->commandLinkButtonWeb, &QCommandLinkButton::clicked,
            this, []
    {
        QDesktopServices::openUrl( QUrl("https://lug.ustc.edu.cn/sites/qtguide/") );
    });
}

Widget::~Widget()
{
    delete ui;
}
//检查兴趣爱好，同步更新三态复选框的状态
void Widget::CheckHobbies()
{
    int count = 0; //兴趣计数
    if ( ui->checkBoxRead->isChecked() )
        count++;
    if ( ui->checkBoxClimb->isChecked() )
        count++;
    if ( ui->checkBoxSwim->isChecked() )
        count++;
    if ( ui->checkBoxDaze->isChecked() )
        count++;
    if ( ui->checkBoxShopping->isChecked() )
        count++;
    if ( ui->checkBoxEat->isChecked() )
        count++;

    //根据兴趣计数设置三态按钮的状态
    if ( count <= 0)
    {
        ui->checkBoxTristate->setCheckState(Qt::Unchecked);
        return;
    }
    else if ( count <= 5 )
    {
        ui->checkBoxTristate->setCheckState(Qt::PartiallyChecked);
        return;
    }
    else
    {
        ui->checkBoxTristate->setCheckState(Qt::Checked);
        return;
    }
}
//显示弹窗
void Widget::on_pushButton_clicked()
{
    QString strResult = tr("兴趣爱好为：\r\n");
    if ( ui->checkBoxRead->isChecked() )
        strResult += tr("读书\r\n");
    if ( ui->checkBoxClimb->isChecked() )
        strResult += tr("爬山\r\n");
    if ( ui->checkBoxSwim->isChecked() )
        strResult += tr("游泳\r\n");
    if ( ui->checkBoxDaze->isChecked() )
        strResult += tr("发呆\r\n");
    if ( ui->checkBoxShopping->isChecked() )
        strResult += tr("逛街\r\n");
    if ( ui->checkBoxEat->isChecked() )
        strResult += tr("吃货\r\n");
    //弹窗显示
    QMessageBox::information(this, tr("兴趣爱好"), strResult);
}

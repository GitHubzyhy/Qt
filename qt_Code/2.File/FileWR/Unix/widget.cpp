#include "widget.h"
#include "./ui_widget.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator> //正则表达式验证器，检验IP
#include <QIntValidator>    //整数验证器，检验端口
#include <QFileDialog>      //打开和保存文件对话框
#include <QFile>            //读写文件

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //定义 IPv4 正则表达式，注意 "\\" 就是一个反斜杠
    QRegularExpression re("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}"
                          "(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");

    QRegularExpressionValidator *reVali = new QRegularExpressionValidator(re);//新建正则表达式验证器
    ui->lineEditIP->setValidator(reVali);//设置给 lineEditIP
    QIntValidator *intVali = new QIntValidator(0, 65535);//新建整数验证器
    ui->lineEditPort->setValidator(intVali);//设置给 lineEditPort
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonBrowseSrc_clicked()
{
    //打开配置文件
    QString strSrcName = QFileDialog::getOpenFileName(
                             this, tr("打开配置文件"),
                             tr("."),
                             tr("Text files(*.txt);;All files(*)")
                         );
    if ( !strSrcName.isEmpty() )
        ui->lineEditSrcFile->setText(strSrcName);//设置源文件名
}

void Widget::on_pushButtonLoad_clicked()
{
    //加载配置
    QString strSrc = ui->lineEditSrcFile->text(); //获取源文件路径
    if (strSrc.isEmpty()) return; //没设置文件名

    QFile fileIn(strSrc); //定义文件对象
    if (!fileIn.open(QIODevice::ReadOnly)) //用只读的方式打开
    {
        //打开错误
        QMessageBox::warning(this, tr("打开错误")
                             , tr("打开文件错误：") + fileIn.errorString());
        return; //不处理文件
    }

    while (!fileIn.atEnd())
    {
        //一行行读取的
        QByteArray baLine = fileIn.readLine(); //游标++
        baLine = baLine.trimmed(); //剔除首尾空格
        //判断是否为注释行
        if ( baLine.startsWith('#') )
            continue; //不处理注释行
        //正常的设置行，分析这一行的配置项
        AnalyzeOneLine(baLine);
    }
    //提示加载完毕
    QMessageBox::information(this, tr("加载配置"), tr("加载配置项完毕！"));
}

void Widget::on_pushButtonBrowseDst_clicked()
{
    //保存文件名
    QString strDstName = QFileDialog::getSaveFileName(
                             this,
                             tr("保存配置文件"),
                             tr("."),
                             tr("Text files(*.txt);;All files(*)")
                         );
    if (!strDstName.isEmpty())
        ui->lineEditDstFile->setText(strDstName); //设置要保存的文件名
}

void Widget::on_pushButtonSave_clicked()
{
    //保存配置
    QString strSaveName = ui->lineEditDstFile->text();
    //获取设置值
    QString strIP = ui->lineEditIP->text();
    QString strPort = ui->lineEditPort->text();
    QString strHostName = ui->lineEditHostName->text();
    QString strWorkGroup = ui->lineEditWorkGroup->text();
    //如果字符串有空串就不写入
    if ( strSaveName.isEmpty() || strIP.isEmpty() || strPort.isEmpty()
         || strHostName.isEmpty() || strWorkGroup.isEmpty() )
    {
        QMessageBox::warning(this, tr("保存配置"),
                             tr("需要设置好保存文件名和所有配置项数值。"));
        return;
    }

    //定义文件对象
    QFile fileOut(strSaveName);
    //打开
    if (!fileOut.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("打开文件"),
                             tr("打开目的文件失败：") + fileOut.errorString() );
        return;
    }

    //构造字节数组写入
    //ip 行
    QByteArray baTemp = "ip = ";
    baTemp += strIP.toLocal8Bit() + "\n";
    fileOut.write(baTemp);
    //port 行
    baTemp = "port = ";
    baTemp += strPort.toLocal8Bit() + "\n";
    fileOut.write( baTemp );
    //hostname 行
    baTemp = "hostname = ";
    baTemp += strHostName.toLocal8Bit() + "\n";
    fileOut.write( baTemp );
    //workgroup 行
    baTemp = "workgroup = ";
    baTemp += strWorkGroup.toLocal8Bit() + "\n";
    fileOut.write( baTemp );
    //提示保存成功
    QMessageBox::information(this, tr("保存配置"), tr("保存配置项成功！"));
}

void Widget::AnalyzeOneLine(const QByteArray &baLine)
{
    //分析配置文本
    QList<QByteArray> list = baLine.split('='); //按等号分隔
    if (list.count() < 2) return; //分隔之后没有配置值，无法设置

    //配置项名，剔除空格，变为统一的小写名称
    QByteArray optionName = list[0].trimmed().toLower();
    //配置项的值，只需要剔除空格
    QByteArray optionValue = list[1].trimmed();

    QString strValue = QString::fromLocal8Bit(optionValue); //转换成字符串
    //判断哪个配置项
    if ( "ip" == optionName )
    {
        ui->lineEditIP->setText( strValue );
        return;
    }
    if ( "port" == optionName)
    {
        ui->lineEditPort->setText( strValue );
        return;
    }
    if ( "hostname" == optionName )
    {
        ui->lineEditHostName->setText( strValue );
        return;
    }
    if ( "workgroup" == optionName)
    {
        ui->lineEditWorkGroup->setText( strValue );
        return;
    }//如果有其他不相关的配置项名不处理

}

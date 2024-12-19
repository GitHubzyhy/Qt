#include "widget.h"
#include "./ui_widget.h"
#include <QFileDialog>//文件对话框
#include <QProgressDialog>//进度条对话框
#include <QFile>//文件
#include <QCryptographicHash>  //计算MD5
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}
//浏览要打开的文件
void Widget::on_pushButtonBrowser_clicked()
{
    QString strFileName = QFileDialog::getOpenFileName(
                              this,
                              tr("选择文件"),
                              "/home",
                              "All files (*)");
    if ( strFileName.isEmpty() )
    {
        m_dlgErrorMsg.showMessage( tr("文件名为空，未选择文件！") );
        return;
    }
    //文件名非空
    m_strFileName = strFileName;
    ui->lineEditFileName->setText( m_strFileName );
    //清空旧的文本框
    ui->textBrowserInfo->clear();
}
//计算文件 MD5
void Widget::on_pushButtonCalcMD5_clicked()
{
    //先从编辑框获取文件名
    QString strFileName = ui->lineEditFileName->text().trimmed(); //剔除2边空格
    if (strFileName.isEmpty())
    {
        m_dlgErrorMsg.showMessage(tr("打开指定文件失败！"));
        return;
    }

    m_strFileName = strFileName; //文件名非空的情况下
    QFile fileIn(m_strFileName);
    if (!fileIn.open(QIODevice::ReadOnly))
    {
        //打开错误
        QMessageBox::warning(this, tr("打开错误")
                             , tr("打开文件错误：") + fileIn.errorString());
        return; //不处理文件
    }

    //正常打开文件，检查文件大小
    qint64 nFileSize = fileIn.size();
    if ( nFileSize < 1 )
    {
        m_dlgErrorMsg.showMessage( tr("文件大小为 0，没有数据！") );
        fileIn.close();
        return;
    }

    //计算MD5值
    QByteArray baMD5 = CalcFileMD5(fileIn, nFileSize);
    //构造信息字符串
    QString strInfo = tr("文件名：") + m_strFileName;
    strInfo += tr("\n文件大小：%1 字节").arg(nFileSize);
    strInfo += tr("\nMD5校验值：\n");
    strInfo += baMD5.toHex().toUpper();

    ui->textBrowserInfo->setText(strInfo);//设置给文本框
    fileIn.close();
}
//计算文件对象 MD5 值
QByteArray Widget::CalcFileMD5(QFile &fileIn, qint64 nFileSize)
{
    QByteArray baRet, baCurData; //返回的字节数值，数据块
    //定义算法对象
    QCryptographicHash algMD5(QCryptographicHash::Md5);
    if (nFileSize < 100 * 1024 ) //小于 100K
    {
        //一次读取全部数据计算MD5
        baCurData = fileIn.readAll();
        algMD5.addData(baCurData);//添加数据到加密哈希值
        baRet = algMD5.result();//返回最终的哈希值
        return baRet;
    }

    //如果是大于 100K，分块读取数据
    qint64 oneBlockSize = nFileSize / 100; //一次读取多少字节
    int nBlocksCount = 100;
    if ( nFileSize % oneBlockSize != 0 )
    {
        //存在余数除不尽
        nBlocksCount += 1;
    }

    //先设置进度对话框，然后开始循环读取文件内容
    QProgressDialog dlgProgress(tr("正在计算MD5 ..."), tr("取消计算"),
                                0, nBlocksCount, this);
    dlgProgress.setWindowModality(Qt::WindowModal);
    dlgProgress.setMinimumDuration(0);//持续0毫秒就显示进度对话框
    for (int i = 0; i < nBlocksCount; ++i)
    {
        dlgProgress.setValue(i);//设置进度，自动显示对话框
        if (dlgProgress.wasCanceled())
            break;//判断是否取消
        //正常读取数据块，计算MD5
        baCurData = fileIn.read(oneBlockSize);
        algMD5.addData(baCurData);//添加数据到加密哈希值
    }

    //进度没有取消，获取正常MD5结果
    if ( ! dlgProgress.wasCanceled() )
        baRet = algMD5.result();//返回最终的哈希值
    //结束进度
    dlgProgress.setValue( nBlocksCount );
    //返回MD5字节数组
    return baRet;
}

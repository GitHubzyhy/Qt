#include "qformdoc.h"
#include "ui_qformdoc.h"
#include <QMessageBox>
#include <QFile>
#include <QFileInfo>
#include <QFontDialog>

QFormDoc::QFormDoc(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QFormDoc)
{
    ui->setupUi(this);
    setWindowTitle(tr("New Doc"));//窗口标题
    setAttribute(Qt::WA_DeleteOnClose);//关闭时自动删除
}

QFormDoc::~QFormDoc()
{
    QMessageBox::information(this, "信息", "文档窗口被释放");//窗口关闭之后提示
    delete ui;
}

void QFormDoc::loadFormFile(QString &aFileName)
{
    //打开文件，并将文件内容读取plainTextEdit中
    QFile aFile(aFileName);

    if(aFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //读取文件并讲内容放入plainTextEdit
        QTextStream aStream(&aFile);
        aStream.setAutoDetectUnicode(true);//防止乱码

        ui->plainTextEdit->clear();//删除文本编辑中的所有文本。
        ui->plainTextEdit->setPlainText(aStream.readAll());//将文本流中的数据全部读出来
        aFile.close();
        //根据文件名获取文件信息，将文件名设置MDI窗体的标题
        mCurrentFile = aFileName;
        QFileInfo fileInfo(aFileName);//文件信息
        QString str = fileInfo.fileName(); //去除路径后的文件名
        setWindowTitle(str);//重新设置窗口标题
        mFileOpened = true; //表示当前文件已经打开
    }
}

QString QFormDoc::currentFileName()
{
    //返回当前文件名
    return mCurrentFile;
}

bool QFormDoc::isFileOpened()
{
    //判断文件是否已打开
    return mFileOpened;
}

void QFormDoc::setEditFont()
{
    //设置字体
    QFont font = ui->plainTextEdit->font();
    bool ok;
    font = QFontDialog::getFont(&ok, font);
    ui->plainTextEdit->setFont(font);
}

void QFormDoc::textCut()
{
    ui->plainTextEdit->cut();
}

void QFormDoc::textCopy()
{
    ui->plainTextEdit->copy();
}

void QFormDoc::textPaste()
{
    ui->plainTextEdit->paste();
}

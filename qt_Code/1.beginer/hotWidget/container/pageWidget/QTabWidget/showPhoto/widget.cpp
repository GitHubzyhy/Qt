#include "widget.h"
#include "./ui_widget.h"
#include "tabpreview.h"
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_pTabPreview = new TabPreview;//新建文件预览标签页 第三个标签页
    ui->tabWidget->addTab(m_pTabPreview, tr("文件预览"));
    //关联信号和槽函数，更新文件名
    connect( this, SIGNAL(fileNameChanged(QString)),
             m_pTabPreview, SLOT(onFileNameChanged(QString)) );
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonSelectFile_clicked()
{
    QString strName = QFileDialog::getOpenFileName(this, tr("选择文件"),
                      tr(""), tr("All files(*)") );
    strName = strName.trimmed(); //剔除首位空格
    if ( strName.isEmpty() )
        return; //没有文件名

    //获取了文件名
    m_strFileName = strName;
    m_fileInfo.setFile( m_strFileName );

    qint64 nFileSize = m_fileInfo.size();//文件字节大小

    //设置“文件名称”的标签页控件
    ui->lineEditFullName->setText( m_strFileName );
    ui->lineEditShortName->setText( m_fileInfo.fileName() );
    ui->lineEditFileSize->setText( tr("%1 字节").arg( nFileSize ) );

    //三个时间 创建时间，最后一次被读取的时间，最后一次被修改的时间
    QString strTimeCreated = m_fileInfo.birthTime().toString("yyyy-MM-dd  HH:mm:ss");
    QString strTimeRead = m_fileInfo.lastRead().toString("yyyy-MM-dd  HH:mm:ss");
    QString strTimeModified = m_fileInfo.lastModified().toString("yyyy-MM-dd  HH:mm:ss");

    //设置“文件时间”的标签页控件显示
    ui->lineEditTimeCreated->setText( strTimeCreated );
    ui->lineEditTimeRead->setText( strTimeRead );
    ui->lineEditTimeModified->setText( strTimeModified );

    //触发文件名称修改的信号
    emit fileNameChanged(m_strFileName);
}

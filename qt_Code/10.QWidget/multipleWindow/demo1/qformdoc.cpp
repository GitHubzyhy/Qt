#include "qformdoc.h"
#include "ui_qformdoc.h"
#include <QToolBar>
#include <QLayout>
#include <QMessageBox>
#include <QFile>
#include <QFileInfo>
#include <QFontDialog>
#include <QFileDialog>

QFormDoc::QFormDoc(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QFormDoc)
{
    ui->setupUi(this);
    QToolBar *locToolBar = new QToolBar(tr("文档"), this); //创建工具栏
    locToolBar->addAction(ui->actOpen);
    locToolBar->addAction(ui->actFont);
    locToolBar->addSeparator();//添加一个分隔符
    locToolBar->addAction(ui->actCut);
    locToolBar->addAction(ui->actCopy);
    locToolBar->addAction(ui->actPaste);
    locToolBar->addAction(ui->actUndo);
    locToolBar->addAction(ui->actRedo);
    locToolBar->addSeparator();
    locToolBar->addAction(ui->actClose);
    locToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QVBoxLayout *Layout = new QVBoxLayout();
    Layout->addWidget(locToolBar); //设置工具栏和编辑器上下布局
    Layout->addWidget(ui->plainTextEdit);
    Layout->setContentsMargins(2, 2, 2, 2); //减小边框的宽度
    Layout->setSpacing(2);
    this->setLayout(Layout); //设置布局

    connectFunction();//构造一系列信号槽
}

QFormDoc::~QFormDoc()
{
    QMessageBox::information(this, "消息", "QFormDoc对象被删除和释放");
    emit dialogClose();//发射信号
    delete ui;
}

void QFormDoc::openFile()
{
    QString aFileName = QFileDialog::getOpenFileName(this, tr("打开已有文件"), "C:\\");
    loadFormFile(aFileName);//将文件名放到加载函数里面
}

void QFormDoc::loadFormFile(QString &aFileName)
{
    QFile aFile(aFileName);

    if(aFile.open(QIODevice::ReadOnly | QIODevice::Text)) //用只读的方式和text方式打开文件
    {
        QTextStream aStream(&aFile);//将文件绑定文本流
        aStream.setAutoDetectUnicode(true);//防止乱码

        ui->plainTextEdit->clear();//每次加载的时候都要情况
        ui->plainTextEdit->setPlainText(aStream.readAll());

        aFile.close();
        QFileInfo fileInfo(aFileName);//用于提起文件的信息
        QString str = fileInfo.fileName(); //返回不包括路径的文件名
        setWindowTitle(str);
    }
}

void QFormDoc::setEditFont()
{
    QFont font = ui->plainTextEdit->font();
    bool ok;
    font = QFontDialog::getFont(&ok, font, this, "QFontDialog");
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

void QFormDoc::textUndo()
{
    ui->plainTextEdit->undo();
}

void QFormDoc::textRedo()
{
    ui->plainTextEdit->redo();
}

void QFormDoc::connectFunction()
{
    connect(ui->actOpen, &QAction::triggered, this, &QFormDoc::openFile);
    connect(ui->actFont, &QAction::triggered, this, &QFormDoc::setEditFont);
    connect(ui->actCut, &QAction::triggered, this, &QFormDoc::textCut);
    connect(ui->actCopy, &QAction::triggered, this, &QFormDoc::textCopy);
    connect(ui->actPaste, &QAction::triggered, this, &QFormDoc::textPaste);
    connect(ui->actUndo, &QAction::triggered, this, &QFormDoc::textUndo);
    connect(ui->actRedo, &QAction::triggered, this, &QFormDoc::textRedo);
}

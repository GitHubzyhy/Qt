#include "widget.h"
#include "./ui_widget.h"
#include <QFileDialog>
#include <QUrl>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->plainTextEdit->setReadOnly(true);//设置 QPlainTextEdit 只读模式
    //设置 QTextBrowser 能自动用系统浏览器打开外站链接
    ui->textBrowser->setOpenExternalLinks(true);

    //将 "后退"、"前进"按钮设置为不可用状态
    ui->btnBackward->setEnabled(false);
    ui->btnForeward->setEnabled(false);

    //关联前进后退按钮到QTextBrower的槽函数
    connect(ui->btnBackward, SIGNAL(clicked()),
            ui->textBrowser, SLOT(backward()));
    connect(ui->btnForeward, &QPushButton::clicked,
            ui->textBrowser, &QTextBrowser::forward);
}

Widget::~Widget()
{
    delete ui;
}
//打开html
void Widget::on_btnOpen_clicked()
{
    QUrl urlFile = QFileDialog::getOpenFileUrl(
                       this,
                       "open HTML",
                       QUrl(),
                       "HTML files(*.htm *.html)");
    if (!urlFile.isEmpty())
    {
        //打印文件链接
        qDebug() << urlFile;
        ui->textBrowser->setSource(urlFile);//设置浏览的源文件
    }
}
//根据能否后退，设置 "后退" 按钮可用状态
void Widget::on_textBrowser_backwardAvailable(bool arg1)
{
    ui->btnBackward->setEnabled(arg1);
}
//根据能否前进，设置 "前进" 按钮可用状态
void Widget::on_textBrowser_forwardAvailable(bool arg1)
{
    ui->btnForeward->setEnabled(arg1);
}
//当 QTextBrowser 控件内容变化时，QPlainTextEdit 跟着变化
void Widget::on_textBrowser_textChanged()
{
    //获取 html 字符串，设置给 plainTextEdit
    QString strHtml = ui->textBrowser->toHtml();//父类的成员函数
    ui->plainTextEdit->setPlainText(strHtml);
}

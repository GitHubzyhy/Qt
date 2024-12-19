#include "qwdialogheaders.h"
#include "ui_qwdialogheaders.h"
#include <QStringListModel>
#include <QMessageBox>

QWDialogHeaders::QWDialogHeaders(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QWDialogHeaders)
{
    ui->setupUi(this);

    model = new QStringListModel;
    ui->listView->setModel(model);
}

QWDialogHeaders::~QWDialogHeaders()
{
    QMessageBox::information(this, tr("自定义表头对话框"), "自定义表头对话框被析构");
    delete ui;
}

void QWDialogHeaders::setHeaderList(QStringList &header)
{
    model->setStringList(header);//初始化数据模型
}

QStringList QWDialogHeaders::headerList()
{
    return model->stringList();//返回数据模型的字符串列表
}

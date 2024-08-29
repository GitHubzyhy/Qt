#include "qwdialogheaders.h"
#include "ui_qwdialogheaders.h"
#include <QStringListModel>
#include <QMessageBox>

QWDialogHeaders::QWDialogHeaders(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QWDialogHeaders)
{
    ui->setupUi(this);

    model = new QStringListModel(this);
    ui->listView->setModel(model);
}

QWDialogHeaders::~QWDialogHeaders()
{
    QMessageBox::information(this, tr("自定义表头对话框"), tr("自定义表头对话框被析构"));
    delete ui;
}

void QWDialogHeaders::setHeaderList(QStringList &header)
{
    model->setStringList(header);
}

QStringList QWDialogHeaders::headerList()
{
    return model->stringList();
}

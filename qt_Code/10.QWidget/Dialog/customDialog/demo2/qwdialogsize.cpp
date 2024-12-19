#include "qwdialogsize.h"
#include "ui_qwdialogsize.h"
#include <QMessageBox>

QWDialogSize::QWDialogSize(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QWDialogSize)
{
    ui->setupUi(this);
}

QWDialogSize::~QWDialogSize()
{
    QMessageBox::information(this, tr("提示"), "设置行列对话框已删除");
    delete ui;
}

int QWDialogSize::rowCount()
{
    return ui->spinBoxRow->value();
}

int QWDialogSize::columnCount()
{
    return ui->spinBoxColumn->value();
}

void QWDialogSize::setRowColumn(int row, int column)
{
    //初始化数据显示
    ui->spinBoxColumn->setValue(row);
    ui->spinBoxRow->setValue(column);
}

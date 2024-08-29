#include "QWDialogSize.h"
#include "ui_qWDialogSize.h"
#include <QMessageBox>

QWDialogSize::QWDialogSize(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QWDialogSize)
{
    ui->setupUi(this);
}

QWDialogSize::~QWDialogSize()
{
    QMessageBox::information(this, tr("提示"), tr("设置行列对话框已删除"));
    delete ui;
}

int QWDialogSize::rowCount()
{
    return ui->spinRow->value();
}

int QWDialogSize::columnCount()
{
    return ui->spinColumn->value();
}

void QWDialogSize::setRowColumn(const int &row, const int &column)
{
    ui->spinRow->setValue(row);
    ui->spinColumn->setValue(column);
}

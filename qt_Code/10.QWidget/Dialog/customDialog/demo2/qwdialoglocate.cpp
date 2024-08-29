#include "qwdialoglocate.h"
#include "ui_qwdialoglocate.h"
#include "mainwindow.h"

QWDialogLocate::QWDialogLocate(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QWDialogLocate)
{
    ui->setupUi(this);
}

QWDialogLocate::~QWDialogLocate()
{
    delete ui;
}
//计数器
void QWDialogLocate::setSpinRange(int rowCount, int colCount)
{
    //用于设置该对话框中两个spinBox组件可以显示的最大值
    ui->spinBoxRow->setMaximum(rowCount - 1);
    ui->spinBoxColumn->setMaximum(colCount - 1);
}

void QWDialogLocate::setSpinValue(int rowNo, int colNo)
{
    //根据当前选择的行，列来设置两个spinBox组件显示的值
    ui->spinBoxRow->setValue(rowNo);
    ui->spinBoxColumn->setValue(colNo);
}
//设置文字
void QWDialogLocate::on_btnSetText_clicked()
{
    //定位到单元格，并且设置字符串
    int row = ui->spinBoxRow->value();
    int col = ui->spinBoxColumn->value();
    MainWindow *parWind = (MainWindow *)parentWidget(); //获取主窗口
    parWind->setACellText(row, col, ui->lineEdit->text());//调用主窗口函数

    if (ui->ckRow->isChecked()) //行增
        ui->spinBoxRow->setValue(1 + ui->spinBoxRow->value());

    if (ui->ckColumn->isChecked()) //列增
        ui->spinBoxColumn->setValue(1 + ui->spinBoxColumn->value());

}

void QWDialogLocate::closeEvent(QCloseEvent *event)
{
    //窗口关闭event
    MainWindow *parWind = (MainWindow *)parentWidget(); //获取父窗口指针
    parWind->setActLocateEnable(true);//让act_cell启用
    parWind->setDlgLocateNull();//让mainwindow中这个自定义窗口的指针==nullptr
}

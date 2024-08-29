#include "dlg_addstu.h"
#include "ui_dlg_addstu.h"
#include "stusql.h"
#include <QMessageBox>

Dlg_AddStu::Dlg_AddStu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dlg_AddStu)
{
    ui->setupUi(this);
}

Dlg_AddStu::~Dlg_AddStu()
{
    delete ui;
}
//判断是否使添加还是修改
void Dlg_AddStu::setType(bool isAdd, StuInfo info)
{
    m_isAdd = isAdd; //是否添加
    if (m_isAdd) setWindowTitle("添加学生");
    else setWindowTitle("更新学生");
    m_info = info;

    ui->le_name->setText(info.name);//获取输入框的文本
    ui->sb_age->setValue(info.age);
    ui->le_class->setText(QString::number(info.uiclass));
    ui->le_seq->setText(QString::number(info.studentid));
    ui->le_grade->setText(QString::number(info.grade));
    ui->le_phone->setText(info.phone);
    ui->le_wechat->setText(info.wechat);
}

StuInfo Dlg_AddStu::getInfo() const
{
    return m_info;
}

void Dlg_AddStu::on_btn_save_clicked()
{
    auto ptr = stuSql::getinstance(); //返回的是一个指针

    /*获取输入图形化界面的数据到m_info中 为了后续保存到数据库中*/
    m_info.name = ui->le_name->text(); //获取输入框的文本
    m_info.age = ui->sb_age->text().toUInt();
    m_info.uiclass = ui->le_class->text().toInt();
    m_info.grade = ui->le_grade->text().toInt();
    m_info.phone = ui->le_phone->text();
    m_info.wechat = ui->le_wechat->text();
    m_info.studentid = ui->le_seq->text().toInt();
    if (m_isAdd) //判断是添加还是更新
    {
        if (!ptr->addStu(m_info)) //添加到数据库中
            QMessageBox::information(nullptr, "信息", "添加失败！");
    }
    else
    {
        if (!ptr->updateStuInfo(m_info)) //修改到数据库中
            QMessageBox::information(nullptr, "信息", "修改失败！");
    }

    this->hide();
}

void Dlg_AddStu::on_btn_cancel_clicked()
{
    this->hide();
}

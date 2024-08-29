#ifndef DLG_ADDSTU_H
#define DLG_ADDSTU_H

#include <QDialog>
#include<stusql.h>

namespace Ui
{
    class Dlg_AddStu;
}

class Dlg_AddStu : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_AddStu(QWidget *parent = nullptr);
    ~Dlg_AddStu();

    void setType(bool isAdd, StuInfo info = {}); //判断是否使添加还是修改
    StuInfo getInfo() const;

private slots:
    void on_btn_save_clicked();
    void on_btn_cancel_clicked();

private:
    Ui::Dlg_AddStu *ui;

    bool m_isAdd;//判断是否是添加
    StuInfo m_info;//更新数据需要
};

#endif // DLG_ADDSTU_H

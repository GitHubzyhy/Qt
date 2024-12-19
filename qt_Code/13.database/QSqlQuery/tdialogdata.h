#ifndef TDIALOGDATA_H
#define TDIALOGDATA_H

#include <QDialog>
#include <QSqlRecord>//用于在 Qt 的数据库操作中处理和存储数据库查询结果。

namespace Ui
{
    class Tdialogdata;
}

class TdialogData : public QDialog
{
    Q_OBJECT
public:
    explicit TdialogData(QWidget *parent);
    ~TdialogData();

    QSqlRecord record() ;
    void setRecord(const QSqlRecord &newRecord);

private slots:
    //设置清除照片
    void on_btnSetPhoto_clicked();
    void on_btnClearPhoto_clicked();

private:
    Ui::Tdialogdata *ui;
    QSqlRecord m_record;
};

#endif // TDIALOGDATA_H

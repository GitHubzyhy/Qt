#ifndef QWDIALOGHEADERS_H
#define QWDIALOGHEADERS_H

#include <QDialog>

namespace Ui
{
    class QWDialogHeaders;
}

class QStringListModel;
class QWDialogHeaders : public QDialog
{
    Q_OBJECT

public:
    explicit QWDialogHeaders(QWidget *parent = nullptr);
    ~QWDialogHeaders();

    void setHeaderList(QStringList &header);//初始化数据模型
    QStringList headerList();//返回数据模型的字符串列表

private:
    Ui::QWDialogHeaders *ui;
    QStringListModel *model;//数据模型，用于填充QListView组件
};

#endif // QWDIALOGHEADERS_H

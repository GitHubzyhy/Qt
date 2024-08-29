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

    void setHeaderList(QStringList &header);//设置数据模型的值
    QStringList headerList();

private:
    Ui::QWDialogHeaders *ui;
    QStringListModel *model = nullptr;
};

#endif // QWDIALOGHEADERS_H

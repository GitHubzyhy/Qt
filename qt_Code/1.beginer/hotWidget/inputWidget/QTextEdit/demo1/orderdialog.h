#ifndef ORDERDIALOG_H
#define ORDERDIALOG_H

#include <QDialog>

namespace Ui
{
    class OrderDialog;
}

class OrderDialog : public QDialog//自定义对话框
{
    Q_OBJECT

public:
    using OrderItemType = QPair<QString, int>; //取的一个别名
    explicit OrderDialog(QWidget *parent = nullptr);
    ~OrderDialog();

    QString senderName()const;//返回发送者的姓名
    QString senderAddress()const;//返回发送者的地址
    bool sendOffers();//判断checkBox
    QList<OrderItemType> orderItems() const;//返回tableWidget里面的 -项-
private:
    Ui::OrderDialog *ui;
    void setupOrderItem();//建立表格
};

#endif // ORDERDIALOG_H

#include "orderdialog.h"
#include "ui_orderdialog.h"

OrderDialog::OrderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OrderDialog)
{
    ui->setupUi(this);
    setupOrderItem();
}

OrderDialog::~OrderDialog()
{
    delete ui;
}

QString OrderDialog::senderName() const
{
    return ui->lineEditName->text();
}

QString OrderDialog::senderAddress() const
{
    return ui->textEditAddress->toPlainText();
}

bool OrderDialog::sendOffers()
{
    return ui->checkBox->isChecked();
}

QList<OrderDialog::OrderItemType> OrderDialog::orderItems() const
{
    QList<OrderItemType> items;
    //将表格里面的内容一个个拿出来
    for(int row=0;row<ui->tableWidget->rowCount();row++)
    {
        OrderItemType item;
        item.first=ui->tableWidget->item(row,0)->text();
        item.second=ui->tableWidget->item(row,1)->text().toInt();//是int类型
        items.append(item);
    }
    return items;
}

void OrderDialog::setupOrderItem()
{
    QStringList headers{"名称"," 数量"};
    QStringList items;
    items<<"小汽车"<<"射水抢"<<"参考书"<<"咖啡杯";

    //设置ui界面的tableWidget
    ui->tableWidget->setRowCount(items.count());//设置多少行
    ui->tableWidget->setColumnCount(headers.count());//设置多少列
    ui->tableWidget->setHorizontalHeaderLabels(headers);//设置水平页眉标签

    //设置tableWidget中的项属性，并且添加到tableWidget中
    for(int row=0;row<items.count();row++)
    {
        QTableWidgetItem *name=new QTableWidgetItem(items[row]);
        name->setTextAlignment(Qt::AlignCenter);//设置文本居中
        ui->tableWidget->setItem(row,0,name);

        QTableWidgetItem *number=new QTableWidgetItem("1");
        number->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row,1,number);
    }
}

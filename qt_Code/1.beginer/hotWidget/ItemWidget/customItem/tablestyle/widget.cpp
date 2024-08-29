#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置行列 4*4
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(4);
    //设置表格水平头，各列均匀分布
    ui->tableWidget->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
    //新建表格条目
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            //新建条目，并根据行号、列号设置文本
            QTableWidgetItem *itemNew = new QTableWidgetItem();
            itemNew->setText( tr("tableItem %1, %2").arg(i).arg(j) );
            ui->tableWidget->setItem( i, j, itemNew );
        }
    }
}

Widget::~Widget()
{
    delete ui;
}
//双色交替行
void Widget::on_pushButtonAlternatingRowColors_clicked()
{
    //启用双色交替行显示
    ui->tableWidget->setAlternatingRowColors(true);
    //定制样式表，交替行采用天蓝色，表格的网格线用深绿色
    QString strStyle = ("QTableWidget::item:alternate { background-color: skyblue;}"
                        "QTableWidget { gridline-color: darkgreen;"
                        " background-color: transparent;}"//背景颜色设置为默认
                       );

    // 添加给表格控件，旧的样式表保留
    ui->tableWidget->setStyleSheet( ui->tableWidget->styleSheet() + strStyle );
}
//选中条目定制
void Widget::on_pushButtonSelectionCustom_clicked()
{
    QString strStyle = "QTableWidget::item:selected { background-color: yellow; "
                       "color: red; "
                       "border: 1px dashed black; }";
    //添加给表格控件，旧的样式表保留
    ui->tableWidget->setStyleSheet( ui->tableWidget->styleSheet() + strStyle );
    //设置当前条目为高亮色
    QTableWidgetItem *curItem = ui->tableWidget->currentItem();
    if (nullptr != curItem)
    {
        curItem->setSelected(true); //标上选中的高亮色
    }
}
//所有条目定制
void Widget::on_pushButtonItemCustom_clicked()
{
    // QTableWidget::item 就是所有条目的样式表配置
    // color 是前景色，background-color 是背景色
    QString strStyle = " QTableWidget::item{ "
                       "color: blue; "
                       "background-color: lightgreen; "
                       "} " ;
    //设置给表格控件，QTableWidget::item 样式表与前面两个函数的样式表冲突
    ui->tableWidget->setStyleSheet( ui->tableWidget->styleSheet() + strStyle );
}
//角按钮定制
void Widget::on_pushButtonCornerButtonCustom_clicked()
{
    // QTableCornerButton::section 就是设置表格左上角的按钮风格
    QString strStyle = " QTableCornerButton::section{ "
                       " background: green;  "
                       " border: 2px outset green; "
                       "} " ;
    //添加给表格控件，旧的样式表保留
    ui->tableWidget->setStyleSheet( ui->tableWidget->styleSheet() + strStyle );
}
//表头定制
void Widget::on_pushButtonHeaderCustom_clicked()
{
    // QHeaderView 就是表头的类，定制该类的样式表
    //前景色背景色的一般都是 color  和 background-color
    QString strStyle = " QHeaderView{ "
                       "color: darkblue; "
                       "background-color: cyan; "
                       "} " ;
    //添加给表格控件，旧的样式表保留
    ui->tableWidget->setStyleSheet( ui->tableWidget->styleSheet() + strStyle );
}
//清空样式表
void Widget::on_pushButtonClearStyle_clicked()
{
    //打印旧的样式表信息
    qDebug() << "old style sheets: \r\n" << ui->tableWidget->styleSheet() << '\n';
    //置空样式表
    ui->tableWidget->setStyleSheet("");
    //取消双色交替行的显示
    ui->tableWidget->setAlternatingRowColors( false );
}

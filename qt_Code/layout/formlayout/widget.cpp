#include "widget.h"
#include<QtWidgets>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    demo();
}

Widget::~Widget()
{
}

void Widget::formLayout()
{
    //开始表格布局
    auto *nameEdit=new QLineEdit(this);
    auto *addrEdit=new QLineEdit(this);
    auto *occpEdit=new QLineEdit(this);
    auto *formLayout=new QFormLayout(this);

    formLayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter );
    formLayout->addRow("Name: ",nameEdit);
    formLayout->addRow("Email: ",addrEdit);
    formLayout->addRow("Age: ",occpEdit);
}

void Widget::gridLayout()
{
    //网格布局
    auto *grid=new QGridLayout(this);
    grid->setSpacing(2);//控件之间水平和垂直的像素都为2
    QVector<QString> values({ "7", "8", "9", "/",
                             "4", "5", "6", "*",
                             "1", "2", "3", "-",
                             "0", ".", "=", "+" });
    int pos=0;
    for(int i=0;i<4;i++)
        for(int j=0;j<4;++j)
        {
            auto *btn=new QPushButton(values[pos],this);
            btn->setFixedSize(40,40);
            grid->addWidget(btn,i,j);
            pos++;
        }
    setLayout(grid);
}

void Widget::demo()
{
    auto *grid=new QGridLayout(this);//网格布局
    grid->setHorizontalSpacing(15);//设置水平方向控件的间隔默认为15像素
    grid->setVerticalSpacing(10);//设置垂直方向控件的间隔默认为10像素

    auto *title=new QLabel("Title: ",this);
    title->setAlignment(Qt::AlignRight | Qt::AlignVCenter);//水平靠右，垂直居中
    grid->addWidget(title,0,0,1,1);//在第0行第0列，行跨越1格，列跨越1格

    auto *edt_1=new QLineEdit(this);
    grid->addWidget(edt_1,0,1,1,1);

    auto *author=new QLabel("author: ",this);
    author->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    grid->addWidget(author,1,0,1,1);

    auto *edt_2=new QLineEdit(this);
    grid->addWidget(edt_2,1,1,1,1);

    auto *review = new QLabel("Review:", this);
    grid->addWidget(review, 2, 0, 1, 1);
    review->setAlignment(Qt::AlignRight | Qt::AlignTop);

    auto *te = new QTextEdit(this);
    grid->addWidget(te, 2, 1, 3, 1);
    setLayout(grid);


}


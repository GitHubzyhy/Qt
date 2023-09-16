#include "widget.h"
#include<QtWidgets>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{


    Hybird();
}

Widget::~Widget()
{
}

void Widget::Vertical()
{
        auto *settings=new QPushButton("设置",this);
        auto *accounts=new QPushButton("账户",this);
        auto *loans=new QPushButton("存款",this);
        auto *cash=new QPushButton("取款",this);

        //让上下左右都填满
        settings->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        accounts->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        loans->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        cash->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

       //开始QVBoxLayout垂直布局
        auto *vbox=new QVBoxLayout(this);
        vbox->addWidget(settings);
        vbox->addWidget(accounts);
        vbox->addWidget(loans);
        vbox->addWidget(cash);
}

void Widget::Horizontal()
{
        //开始Horizontal水平布局
        auto *vbox=new QVBoxLayout(this);//垂直布局
        auto *hbox=new QHBoxLayout(this);//水平布局

        auto *okBtn=new QPushButton("Ok",this);
        auto *applyBtn=new QPushButton("Apply",this);
        //格子本身占据一因子的空间，控件放在格子的最右边
        hbox->addWidget(okBtn,1,Qt::AlignRight);//第二个参数是拉伸因子决定了控件在布局中水平方向上的相对大小。
        //格子本身占据0因子空间，控件填满整个格子
        hbox->addWidget(applyBtn,0);
        vbox->addStretch(1);//添加一个弹簧，弹簧的拉伸因子为1，弹簧的作用是布局中创建空白区域或调整控件之间的间距
        vbox->addLayout(hbox);
}

void Widget::Hybird()
{
        auto *vbox=new QVBoxLayout();
        auto *hbox=new QHBoxLayout(this);
        auto *lw=new QListWidget(this);//显示一个可选择的列表

        lw->addItem("北京");
        lw->addItem("上海");
        lw->addItem("广州");
        lw->addItem("深圳");
        lw->addItem("南昌");

        auto *add = new QPushButton("添加", this);
        auto *rename = new QPushButton("修改", this);
        auto *remove = new QPushButton("删除", this);
        auto *removeall = new QPushButton("全部删除", this);

        vbox->setSpacing(3);//置整个布局中的默认间距大小为3像素的间距
        vbox->addStretch(1);//添加一个弹簧
        vbox->addWidget(add);
        vbox->addWidget(rename);
        vbox->addWidget(remove);
        vbox->addWidget(removeall);

        hbox->addWidget(lw);
        hbox->addSpacing(15);//布局中添加增加15像素的间距
        hbox->addLayout(vbox);//将垂直布局添加进去

}


#include "Palette.h"
#include <QBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>

Palette::Palette(QWidget *parent)
    : QDialog(parent)
{
    createCtrlFrame();// 完成颜色选取区域的创建
    createContentFrame();// 完成展示区域的创建
    QHBoxLayout *mainLayout = new QHBoxLayout(this);//水平布局
    mainLayout->addWidget(ctrlFrame);//颜色选取的框
    mainLayout->addWidget(contentFrame);//展示框
}

Palette::~Palette() {}

void Palette::createCtrlFrame()
{
    //1. 完成颜色选取区域的创建
    p = &Palette::showWindow;
    createWidget(windowLabel, windowComboBox, tr("QPalette::window: "));//下拉列表插入颜色

    p = &Palette::showWindowText;
    createWidget(windowTextLabel, windowTextComboBox, tr("QPalette::WindowText: "));//窗口前景色

    p = &Palette::showButton;
    createWidget(buttonLabel, buttonComboBox, tr("QPalette::Button: ")); //窗口按钮的颜色

    p = &Palette::showButtonText;
    createWidget(buttonTextLabel, buttonTextComboBox, tr("QPalette::ButtonText: ")); //窗口按钮上面文本的颜色

    p = &Palette::showBase;
    createWidget(baseLabel, baseComboBox, tr("QPalette::Base: "));

    //2. 页面布局
    ctrlFrame = new QFrame; //窗口背景色
    QGridLayout *mainLayout = new QGridLayout(ctrlFrame);//网格布局
    mainLayout->setSpacing(20);//设置所有控件之间的距离

    mainLayout->addWidget(windowLabel, 0, 0);
    mainLayout->addWidget(windowComboBox, 0, 1);

    mainLayout->addWidget(windowTextLabel, 1, 0);
    mainLayout->addWidget(windowTextComboBox, 1, 1);

    mainLayout->addWidget(buttonLabel, 2, 0);
    mainLayout->addWidget(buttonComboBox, 2, 1);

    mainLayout->addWidget(buttonTextLabel, 3, 0);
    mainLayout->addWidget(buttonTextComboBox, 3, 1);

    mainLayout->addWidget(baseLabel, 4, 0);
    mainLayout->addWidget(baseComboBox, 4, 1);
}

void Palette::createWidget(QLabel *&label, QComboBox *&comboBox, const QString &str)
{
    //为控件分配内存和构建下拉列表
    label = new QLabel(str);
    comboBox = new QComboBox;
    fillColorList(comboBox);//下拉列表插入颜色
    connect(comboBox, &QComboBox::activated, this, p);
}

void Palette::createContentFrame()
{
    // 完成展示区域的创建
    contentFrame = new QFrame;
    label1 = new QLabel(tr("请选择一个值："));
    comboBox1 = new QComboBox;
    comboBox1->addItem("1");
    comboBox1->addItem("2");

    label2 = new QLabel(tr("请输入字符串: "));
    lineEdit2 = new QLineEdit;

    textEdit = new QTextEdit;

    QGridLayout *topLayout = new QGridLayout;//网格布局
    topLayout->addWidget(label1, 0, 0);
    topLayout->addWidget(comboBox1, 0, 1);
    topLayout->addWidget(label2, 1, 0);
    topLayout->addWidget(lineEdit2, 1, 1);
    topLayout->addWidget(textEdit, 2, 0, 1, 2);//位置在(2,0)占据了1行2列

    okBtn = new QPushButton(tr("确认"));
    cancelBtn = new QPushButton(tr("取消"));

    QHBoxLayout *bottomLayout = new QHBoxLayout;//水平布局
    bottomLayout->addStretch(1);//添加一个弹簧，拉伸银子为1，后续控件就为0，1:0
    bottomLayout->addWidget(okBtn);
    bottomLayout->addWidget(cancelBtn);

    QVBoxLayout *mainlayout = new QVBoxLayout(contentFrame);//垂直布局
    mainlayout->addLayout(topLayout);//网格布局里面在加入一个布局
    mainlayout->addLayout(bottomLayout);

    okBtn->setAutoFillBackground(true); //允许自动填充，否则部件颜色或者背景无法显示
    cancelBtn->setAutoFillBackground(true);
    contentFrame->setAutoFillBackground(true);

}

void Palette::fillColorList(QComboBox *comboBox)
{
    //下拉列表插入颜色
    QStringList colorList = QColor::colorNames();// 获取内置颜色名列表
    QString color;

    foreach (color, colorList)
    {
        QPixmap pix(QSize(70, 20));//创建QPixmap对象用于颜色显示
        pix.fill(QColor(color));//用给定的颜色填充像素图。
        comboBox->addItem(QIcon(pix), NULL);//添加一个项(包含一个图标)
        comboBox->setIconSize(QSize(70, 20));//设置图标的大小
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);//表示 comboBox 的大小会根据其内容自动调整
    }
}

void Palette::showWindow()
{
    QStringList colorList = QColor::colorNames();// 获取内置颜色名列表
    QColor color = QColor(colorList[windowComboBox->currentIndex()]);//通过当前项索引设置部件的颜色

    QPalette p = contentFrame->palette();//获取该控件的调色版
    p.setColor(QPalette::Window, color);//改变控件背景颜色
    contentFrame->setPalette(p);//设置为修改的面板

    contentFrame->update();//更新小部件

}

void Palette::showWindowText()
{
    QStringList colorList = QColor::colorNames();
    QColor color = colorList[windowTextComboBox->currentIndex()];

    QPalette p = contentFrame->palette();
    p.setColor(QPalette::WindowText, color);//设置部件的前景色
    contentFrame->setPalette(p);

}

void Palette::showButton()
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[buttonComboBox->currentIndex()]);

    QPalette p = contentFrame->palette();
    p.setColor(QPalette::Button, color);//设置调色板中按钮的颜色
    contentFrame->setPalette(p);

    contentFrame->update();

}

void Palette::showButtonText()
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[buttonTextComboBox->currentIndex()]);

    QPalette p = contentFrame->palette();
    p.setColor(QPalette::ButtonText, color);//设置调色版中按钮文字的颜色
    contentFrame->setPalette(p);

}

void Palette::showBase()
{
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[baseComboBox->currentIndex()]);

    QPalette p = contentFrame->palette();
    p.setColor(QPalette::Base, color);//文本输入小部件的颜色
    contentFrame->setPalette(p);

}

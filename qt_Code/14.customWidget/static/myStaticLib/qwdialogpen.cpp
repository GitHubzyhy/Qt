#include "qwdialogPen.h"
#include "ui_qwdialogPen.h"
#include <QColorDialog>

QWDialogPen::QWDialogPen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogPen)
{
    ui->setupUi(this);

    ui->comboBox->clear();//清除组合框，并且移除所有项
    ui->comboBox->addItem("NoPen", 0); //添加一个项目到组合框中
    ui->comboBox->addItem("SolidLine", 1);
    ui->comboBox->addItem("DasshLine", 2);
    ui->comboBox->addItem("DotLine", 3);
    ui->comboBox->addItem("DashDotLine", 4);
    ui->comboBox->addItem("DashDotDotLine", 5);
    ui->comboBox->addItem("CustomDashLine", 6);
    ui->comboBox->setCurrentIndex(0);
}

QWDialogPen::~QWDialogPen()
{
    delete ui;
}

QPen QWDialogPen::getpen()
{
    //通过ui界面的设置返回QPen，通常是在用户选ok后用到
    m_pen.setStyle(Qt::PenStyle(ui->comboBox->currentIndex()));//将当前组合框中的选项设置为笔的类型
    m_pen.setWidth(ui->spinBox->value());//用spinBox里面的值 设置线宽

    //从调色板中获取颜色的操作，调色板是一组颜色和样式定义，用于控制界面元素的外观
    QColor color = ui->btnColor->palette().color(QPalette::Button);
    m_pen.setColor(color);//笔的颜色为ui界面按钮的颜色
    return m_pen;
}

void QWDialogPen::setPen(const QPen &pen)
{
    m_pen = pen;
    ui->spinBox->setValue(pen.width());//设置pen的线宽
    int i = static_cast<int>(pen.style()); //对应ui界面的组合框里面的项 这里i是枚举值
    ui->comboBox->setCurrentIndex(i);//设置组合框的当前索引

    ui->btnColor->setAutoFillBackground(true);//设置该小部件背景是否自动填充
    QColor color = pen.color();
    QString str = QString::asprintf("background-color:rgb(%d,%d,%d)",
                                    color.red(), color.green(), color.blue());
    ui->btnColor->setStyleSheet(str);//设置颜色按钮的样式表
}

QPen QWDialogPen::getPen(QPen iniPen, bool &ok)//ok作为判断用户的选择
{
    QWDialogPen *dlg = new QWDialogPen;
    QPen pen;
    //设置笔的颜色并且用笔的颜色填充按钮，目的是打开这个自定义对话框就有初始化效果
    dlg->setPen(iniPen);

    /*将对话框显示为模态对话框，阻塞直到用户关闭它。*/
    if (dlg->exec() == QDialog::Accepted)
    {
        pen = dlg->getpen(); //如果用户点的ok就从ui界面提取相关信息，并且设置ok的值
        ok = true;
    }
    else
    {
        pen = iniPen;
        ok = false;
    }
    delete dlg;
    dlg = nullptr;

    return pen;
}
//设置颜色的按钮
void QWDialogPen::on_btnColor_clicked()
{
    QColor color = m_pen.color();
    color = QColorDialog::getColor(color);
    if (color.isValid())
    {
        QString str = QString::asprintf("background-color:rgb(%d,%d,%d)",
                                        color.red(), color.green(), color.blue());
        ui->btnColor->setStyleSheet(str);//修改样式表
    }
}

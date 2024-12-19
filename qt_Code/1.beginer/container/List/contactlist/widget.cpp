#include "widget.h"
#include "./ui_widget.h"
#include "contact.h"
#include <QMessageBox>
#include <QFile> //文件
#include <QFileDialog> //文件打开或保存对话框
#include <QDataStream> //数据流
#include <algorithm>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //定义4个联系人，添加到列表对象和列表控件，列表对象和列表控件一直同步
    Contact person[4] = {Contact("Daala", "44444", "North"),
                         Contact("Bob", "22222", "South"),
                         Contact("Carl", "33333", "West"),
                         Contact("Alice", "11111", "East")
                        };
    for (int i = 0; i < 4; ++i)
    {
        m_listContacts.append(person[i]);
        ui->listWidget->addItem(person[i].toString());//添加到控件中
    }

}

Widget::~Widget()
{
    delete ui;
}
//添加联系人
void Widget::on_pushButtonAdd_clicked()
{
    //获取姓名、电话、地址字符串
    QString strName = ui->lineEditName->text().trimmed(); //清除前后的空格
    QString strPhone = ui->lineEditPhone->text().trimmed();
    QString strAddress = ui->lineEditAddress->text().trimmed();

    //姓名不能为空，电话地址可以空
    if (strName.isEmpty())
    {
        QMessageBox::warning(this, tr("姓名检查"), tr("姓名为空，请输入姓名。"));
        return;
    }
    //姓名不空
    Contact person(strName, strPhone, strAddress);
    //添加到列表对象和列表控件
    m_listContacts.push_back(person);//STL风格添加

    QListWidgetItem *item = new QListWidgetItem(person.toString());
    ui->listWidget->addItem(item);//添加到列表控件中

    //选中新条目
    ui->listWidget->setCurrentItem(item);//当前条目是加虚线框的那个
    item->setSelected( true ); //高亮显示
    ui->listWidget->setFocus(); //设置显示焦点
}
//删除联系人
void Widget::on_pushButtonDel_clicked()
{
    //获取当前条目
    QListWidgetItem *curItem = ui->listWidget->currentItem();
    if (nullptr == curItem) return;
    //存在当前条目
    //获取当前条目的序号
    int ix = ui->listWidget->currentRow();
    //从列表对象删除联系人 并且释放该元素内存
    m_listContacts.removeAt(ix);
    //列表控件同步删除
    delete curItem;
    curItem = nullptr;
}
//查找联系人
void Widget::on_pushButtonFind_clicked()
{
    //获取姓名字符串
    QString strName = ui->lineEditName->text().trimmed();
    //判断是否为空
    if ( strName.isEmpty() ) //姓名为空，不需要查询
    {
        QMessageBox::warning(this, tr("姓名检查"), tr("姓名为空，无法查询。"));
        return;
    }
    //存在姓名
    //从列表对象查找序号
    int ix = m_listContacts.indexOf( Contact(strName, "", "") );
    if (ix == -1) //如果找不到返回 -1
    {
        QMessageBox::information(this, tr("查找"), tr("没有找到姓名一样的联系人。"));
        return;
    }
    else//找到了
    {
        QMessageBox::information(this, tr("查找"),
                                 tr("存在姓名匹配的联系人，序号为 %1 ").arg(ix) );
        //设置列表控件当前选中条目为该序号
        ui->listWidget->setCurrentRow(ix);
        ui->listWidget->currentItem()->setSelected(true); //高亮色
        ui->listWidget->setFocus(); //显示焦点
    }
}
//姓名排序
void Widget::on_pushButtonSort_clicked()
{
    int nCount = ui->listWidget->count(); //获取计数
    if (nCount <= 1) return; //没有联系人或者只有 1 个，不需要排序
    //存在 2 个以上联系人，直接调用排序函数
    std::sort(m_listContacts.begin(), m_listContacts.end());
    //清空列表控件，然后按照排序后的结果显示
    ui->listWidget->clear();
    for (int i = 0; i < nCount; i++)
        ui->listWidget->addItem(m_listContacts[i].toString());
    //列表控件和列表对象的同步完毕
}
//保存到文件 *.ds
void Widget::on_pushButtonSave_clicked()
{
    //获取计数
    int nCount = ui->listWidget->count();
    if (nCount < 1) return; //没有元素
    //存在元素，先获取要打开的文件名
    QString strFile = QFileDialog::getSaveFileName(
                          this,
                          tr("保存文件"),
                          tr("./test.ds"),
                          tr("QDataStream Files (*.ds)") );
    if (strFile.isEmpty()) //判断文件名是否为空
        return;//用户没有设置保存的文件名
    QFile fileOut(strFile);
    if (!fileOut.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, tr("保存文件"), tr("打开文件错误：") + fileOut.errorString());
        return;
    }

    //开始序列化
    QDataStream ds(&fileOut);
    //输出到文件只需一句
    ds << m_listContacts; //QList 和 Contact 都有配套的流操作符函数，因此可以这样一句搞定
    //保存成功
    QMessageBox::information(this, tr("保存文件"), tr("保存成功！"));
}
//从文件 *.ds 读取联系人并显示
void Widget::on_pushButtonOpen_clicked()
{
    // 获取要打开的文件名
    QString strFile = QFileDialog::getOpenFileName(this,
                      tr("打开文件"),
                      tr("./test.ds"),
                      tr("QDataStream Files (*.ds)") );
    // 判断是否为空
    if ( strFile.isEmpty() )
        return; //用户没设置要打开的文件名

    QFile fileIn( strFile );
    if ( ! fileIn.open( QIODevice::ReadOnly ) )
    {
        QMessageBox::warning(this, tr("打开文件"), tr("打开文件错误：") + fileIn.errorString());
        return;
    }

    QDataStream dsIn(&fileIn);
    //先清空旧的列表对象和列表控件内容
    m_listContacts.clear();
    ui->listWidget->clear();
    //加载
    dsIn >> m_listContacts; //QList 和 Contact 都有配套的流操作符函数，因此可以这样一句搞定
    //读取完毕，需要同步显示到列表控件
    int nCount = m_listContacts.count();
    for (int i = 0; i < nCount; i++)
        ui->listWidget->addItem( m_listContacts[i].toString() );

    //同步完成
    QMessageBox::information(this, tr("打开文件"), tr("打开文件成功，并已加载联系人列表。"));
}

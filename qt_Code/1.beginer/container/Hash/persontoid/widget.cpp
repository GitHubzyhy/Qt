#include "widget.h"
#include "./ui_widget.h"
#include "person.h"
#include <QFile>
#include <QFileDialog>
#include <QDataStream>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //添加性别
    ui->comboBoxGender->addItem( tr("男") );
    ui->comboBoxGender->addItem( tr("女") );
    //日历控件编辑时，点击右边小按钮弹出日历表
    ui->dateEditBirthday->setCalendarPopup( true );
}

Widget::~Widget()
{
    delete ui;
}
//显示更新后的数据
void Widget::UpdateDataShow()
{
    //清空旧的显示
    ui->listWidget->clear();
    QList<Person> listPersons = m_data.keys(); //获取所有键
    int nCount = listPersons.count(); //个数
    for (int i = 0; i < nCount; ++i)
    {
        //字符串
        QString strLine;
        strLine = listPersons[i].name() + tr("\t")
                  + listPersons[i].gender() + tr("\t")
                  + listPersons[i].birthday().toString( "yyyy-MM-dd" );

        //ID
        quint64 theID = m_data[ listPersons[i] ];
        strLine += tr("\t%1").arg( theID );
        //添加到列表显示
        ui->listWidget->addItem(strLine);
    }//处理完成
}
//保存数据
void Widget::on_pushButtonSaveData_clicked()
{
    if (m_data.isEmpty())return;
    //获取保存文件名
    QString strFile = QFileDialog::getSaveFileName(
                          this,
                          tr("保存数据到文件"),
                          ".",
                          "Data files(*.data);;All files(*)");
    QFile fileOut(strFile);
    if (!fileOut.open(QIODevice::WriteOnly))
    {
        //打开错误
        QMessageBox::warning(this, tr("打开错误")
                             , tr("打开文件错误：") + fileOut.errorString());
        return; //不处理文件
    }

    //文件正常
    QDataStream dsOut(&fileOut);
    dsOut << m_data; //非常简单的一句代码，写入所有数据到文件
    QMessageBox::information(this, tr("保存文件"),
                             tr("保存文件完成：\r\n%1").arg(strFile));
}
//加载数据
void Widget::on_pushButtonLoadData_clicked()
{
    //获取读取的文件名
    QString strFile = QFileDialog::getOpenFileName(
                          this,
                          tr("从文件加载数据"),
                          ".",
                          "Data files(*.data);;All files(*)");
    if ( strFile.isEmpty() )
        return;
    //文件名不空
    QFile fileIn( strFile );
    if ( ! fileIn.open( QIODevice::ReadOnly ) )
    {
        QMessageBox::warning(this, tr("读取文件"),
                             tr("读取文件失败，无法打开该文件：\r\n%1").arg(strFile));
        return;
    }
    //文件正常
    QDataStream dsIn( &fileIn );

    m_data.clear(); //清空旧的
    ui->listWidget->clear();

    dsIn >> m_data;//加载数据
    UpdateDataShow();//更新显示
    QMessageBox::information(this, tr("加载文件"),
                             tr("加载文件完成：\r\n%1").arg(strFile));
}
//添加元素
void Widget::on_pushButtonAdd_clicked()
{
    //检查姓名和ID
    QString strName = ui->lineEditName->text().trimmed();
    if ( strName.isEmpty() )
    {
        QMessageBox::warning(this, tr("检查姓名"), tr("姓名为空，不能添加！"));
        return;
    }

    quint64 nID;
    bool bOK = false; //用于检查转换是否出错
    nID = ui->lineEditID->text().toULongLong( &bOK, 10 );
    if ( ! bOK )
    {
        QMessageBox::warning(this, tr("ID检查"), tr("请输入合法数字ID！"));
        return;
    }

    //性别生日
    QString strGender = ui->comboBoxGender->currentText();
    QDate birthday = ui->dateEditBirthday->date();

    Person pkey(strName, strGender, birthday);//构造 Person
    m_data[pkey] = nID;//添加元素
    UpdateDataShow();//更新显示
}
//删除选中元素
void Widget::on_pushButtonDel_clicked()
{
    //当前条目
    QListWidgetItem *pCurItem = ui->listWidget->currentItem();
    if (nullptr == pCurItem)
        return;
    if (!(pCurItem->isSelected()))
    {
        //未被选中，不删除
        qDebug() << tr("未选中条目，不做删除操作");
        return;
    }

    //将文本转为变量
    QString strAll = pCurItem->data(Qt::DisplayRole).toString();
    QStringList listParas = strAll.split('\t');
    qDebug() << tr("删除元素：") << listParas;
    // 0号是名字，1号是性别，2号是生日，3号是ID
    QDate birthday = QDate::fromString( listParas[2], "yyyy-MM-dd" );
    Person pkey( listParas[0], listParas[1], birthday );
    //删除变量元素
    m_data.remove( pkey );
    //更新显示
    UpdateDataShow();
}
//Person查ID
void Widget::on_pushButtonPersonToID_clicked()
{
    //检查姓名
    QString strName = ui->lineEditName->text().trimmed();
    if ( strName.isEmpty() )
    {
        QMessageBox::warning(this, tr("检查姓名"), tr("姓名为空，不能添加！"));
        return;
    }
    //性别、生日
    QString strGender = ui->comboBoxGender->currentText();
    QDate birthday = ui->dateEditBirthday->date();
    //对象
    Person pkey( strName, strGender, birthday );

    //一定要用 contains 函数查询 key 是否存在
    if ( m_data.contains( pkey ) )
    {
        quint64 nID = m_data[ pkey ];
        QString strInfo = tr("已查询到ID： %1").arg( nID );
        QMessageBox::information(this, tr("Person查ID"), strInfo );
    }
    else
        QMessageBox::information(this, tr("Person查ID"), tr("未查找到。"));
}
//ID查Person
void Widget::on_pushButtonIDToPerson_clicked()
{
    //检查ID
    quint64 nID;
    bool bOK = false; //用于检查转换是否出错
    nID = ui->lineEditID->text().toULongLong( &bOK, 10 );
    if ( ! bOK )
    {
        QMessageBox::warning(this, tr("ID检查"), tr("请输入合法数字ID！"));
        return;
    }
    //根据 value 反查 key
    QList<Person> listKeys = m_data.keys(nID); //匹配值为nID的所有键
    //个数
    int nCount = listKeys.count();
    if ( nCount < 1 )
    {
        QMessageBox::information(this, tr("ID查Person"), tr("未查找到。"));
        return;
    }
    //如果多个人ID相同
    QString strInfo = tr("已查到匹配人名：\r\n");
    for (int i = 0; i < nCount; i++)
        strInfo += listKeys[i].name() + tr("\r\n");
    //提示框
    QMessageBox::information(this, tr("ID查Person"), strInfo);
}

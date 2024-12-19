#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStandardItemModel>
#include <QLabel>
#include <QItemSelectionModel>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent )
    , ui( new Ui::MainWindow )
{
    ui->setupUi( this );

    setupModel();//模型的初始化

    ui->tableView->setModel( model );
    ui->tableView->setSelectionModel( selectModel ); //必须在这个位置
    //分区的调整模式
    ui->tableView->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );

    connect( selectModel, &QItemSelectionModel::currentChanged,
             this, &MainWindow::statusChange ); //当单元格状态改变的时候就触发这个槽函数
    connect( ui->act_rest, &QAction::triggered,
             this, &MainWindow::resetTable );
    initStatus();//状态栏初始化
}

MainWindow::~MainWindow()
{
    delete ui;
}
//模型初始化
void MainWindow::setupModel()
{
    model = new QStandardItemModel( 5, 6, this ); //5*6的二维表
    QStringList headerName{"Depth", "Measured Depth", "Direction", "Offset", "Quality", "Sampled"};
    model->setHorizontalHeaderLabels( headerName );

    initTable();//构造二维表
    selectModel = new QItemSelectionModel( model, this );
}
//创建二维表
void MainWindow::initTable()
{
    //最后一列特殊处理
    QString str = model->headerData( model->columnCount() - 1,
                                     Qt::Horizontal, Qt::DisplayRole ).toString();

    // 循环设置每个项目的文本对齐方式
    for ( int row = 0; row < model->rowCount(); ++row )
    {
        for ( int column = 0; column < model->columnCount(); ++column )
        {
            QStandardItem *aItem = new QStandardItem;
            aItem->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
            model->setItem(row, column, aItem);

            //最后一列特殊处理
            if (column == model->columnCount() - 1)
            {
                aItem = model->item(row, column);
                aItem->setCheckable( true );
                aItem->setData( str, Qt::DisplayRole );
                aItem->setEditable( false );
            }
        }
    }
    ui->tableView->setCurrentIndex(model->index(0, 0));
}

void MainWindow::setItem(int row)
{
    //添加和插入的时候需要创建项 最后一列特殊处理
    QString str = model->headerData( model->columnCount() - 1,
                                     Qt::Horizontal, Qt::DisplayRole ).toString();

    for (int column = 0; column < model->columnCount(); ++column)
    {
        QStandardItem *aItem = new QStandardItem;
        aItem->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
        model->setItem(row, column, aItem);

        if (column == model->columnCount() - 1) //最后一列特殊处理
        {
            aItem = model->item(row, column);
            aItem->setCheckable( true );
            aItem->setData( str, Qt::DisplayRole );
            aItem->setEditable( false );
        }
    }
}
//状态栏初始化
void MainWindow::initStatus()
{
    LabCellPos = new QLabel( this );
    LabCellText = new QLabel( this );
    ui->statusbar->addWidget( LabCellPos );
    ui->statusbar->addWidget( LabCellText );
}
//更新选择模型
void MainWindow::updateSelect( const QModelIndex &index )
{
    selectModel->clearSelection();//清除选择模型中的选择。发出selectionChanged()。
    selectModel->setCurrentIndex( index, QItemSelectionModel::Select );
}
//更新状态栏
void MainWindow::statusChange( const QModelIndex &current )
{
    if ( !current.isValid() ) return; //索引无效

    LabCellPos->setText( QString( "当前单元格：%1行，%2列" ).arg( current.row() ).arg( current.column() ) );
    QVariant data = model->data( current, Qt::DisplayRole ); // 获取索引处的数据
    QString text = data.toString();
    LabCellText->setText( QString( "单元格内容：%1" ).arg( text ) );
}
//添加行
void MainWindow::on_act_addRow_triggered()
{
    QStandardItem *item = new QStandardItem;
    model->appendRow( item );
    updateSelect( model->index( model->rowCount() - 1, 0 ) ); //更新选择模型
    setItem(ui->tableView->currentIndex().row());//给新增的行添加项

    //显示编辑状态
    ui->tableView->edit(model->index(model->rowCount() - 1, 0));
}
//插入行
void MainWindow::on_act_insertRow_triggered()
{
    QModelIndex curIndex = ui->tableView->currentIndex();//获取屏幕的选中索引
    if (!curIndex.isValid()) return;

    QStandardItem *item = new QStandardItem( "插入的项" );
    model->insertRow( curIndex.row(), item );

    updateSelect( model->index( curIndex.row(), 0 ) ); //更新选择模型
    setItem(curIndex.row());//设置项

    //显示编辑状态
    ui->tableView->edit( model->index( curIndex.row(), 0 ));
}
//删除行
void MainWindow::on_act_deleteRow_triggered()
{
    QModelIndex curIndex = ui->tableView->currentIndex();
    if (curIndex.isValid())
        model->removeRow( curIndex.row() );
}
//表格复位
void MainWindow::resetTable( int rowCount )
{
    rowCount = (rowCount == 0) ? 5 : rowCount;
    model->removeRows( 0, model->rowCount() ); //列数没有被删除
    model->setRowCount(rowCount);
    initTable();//创建二维表
}
//打开stm文件
void MainWindow::on_act_stm_open_triggered()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getOpenFileName( this, "打开一个文件",
                        curPath, "Qt预定义编码文件(*.stm)" );
    if ( aFileName.isEmpty() )
        return;

    QFile aFile( aFileName ); //负责打开文件
    if ( !( aFile.open( QIODevice::ReadOnly ) ) ) //以只写和重写的方式打开文件
        return;

    QDataStream aStream( &aFile );
    aStream.setVersion( QDataStream::Qt_6_6 ); //写入和读取版本要兼容

    qint16 rowCount = 0;
    qint16 colCount = 0;
    aStream >> rowCount >> colCount;//读取行数和列数
    resetTable( rowCount ); //表格复位，设定行数

    QString str;
    qint16 ceShen = 0;
    qreal chuiShen = 0, fangWei = 0, weiYi = 0;
    QString zhiLiang;
    bool quYang = 0;
    QStandardItem *aItem = nullptr;
    QModelIndex index;
    for ( int i = 0; i < colCount; ++i )
        aStream >> str;//读取表头字符串

    //读取数据区数据
    for ( int i = 0; i < rowCount; ++i )
    {
        aStream >> ceShen;
        index = model->index( i, 0 );
        aItem = model->itemFromIndex( index );
        aItem->setData( ceShen, Qt::DisplayRole ); //设置数据

        aStream >> chuiShen; //垂深，qreal
        index = model->index( i, 1 );
        aItem = model->itemFromIndex ( index );
        aItem->setData ( chuiShen, Qt::DisplayRole );

        aStream >> fangWei; //方位，qreal
        index = model->index( i, 2 );
        aItem = model->itemFromIndex ( index ) ;
        aItem->setData( fangWei, Qt::DisplayRole );

        aStream >> weiYi; //位移，qreal
        index = model->index( i, 3 );
        aItem = model->itemFromIndex ( index );
        aItem->setData( weiYi, Qt::DisplayRole );

        aStream >> zhiLiang; //固井质量，QString
        index = model->index( i, 4 );
        aItem = model->itemFromIndex ( index ) ;
        aItem->setData ( zhiLiang, Qt::DisplayRole );

        aStream >> quYang; //测井取样
        index = model->index( i, 5 );
        aItem = model->itemFromIndex( index );

        if ( quYang )
            aItem->setCheckState( Qt::Checked );
        else
            aItem->setCheckState ( Qt::Unchecked ) ;
    }

    aFile.close();
    QMessageBox::information( this, "消息提示", "stm文件打开成功" );
}
//保存stm文件
void MainWindow::on_act_stm_save_triggered()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getSaveFileName( this, "保存stm文件",
                        curPath, "Qt预定义编码文件(*.stm)" );

    QFile aFile( aFileName ); //负责打开文件
    if ( !( aFile.open( QIODevice::WriteOnly | QIODevice::Truncate ) ) ) //以只写和重写的方式打开文件
        return;

    QDataStream aStream(&aFile);
    aStream.setVersion( QDataStream::Qt_6_6 ); //写入和读取版本要兼容

    qint16 rowCount = model->rowCount();
    qint16 colCount = model->columnCount();
    aStream << rowCount << colCount;

    //获取表头文字
    for ( int i = 0; i < model->columnCount(); ++i )
    {
        QString str = model->horizontalHeaderItem(i)->text();
        aStream << str;
    }

    QStandardItem *aItem;
    //获取数据区的数据
    for ( int i = 0; i < model->rowCount(); ++i )
    {
        aItem = model->item( i, 0 ); //测深
        qint16 ceShen = aItem->data( Qt::DisplayRole ).toInt();
        aStream << ceShen;

        aItem = model->item( i, 1 ); //垂深
        qreal chuiShen = aItem->data( Qt::DisplayRole ).toFloat();
        aStream << chuiShen;//写入文件流

        aItem = model->item( i, 2 ); //方位
        qreal fangWei = aItem->data( Qt::DisplayRole ).toFloat();
        aStream << fangWei;

        aItem = model->item( i, 3 ); //位移
        qreal weiYi = aItem->data( Qt::DisplayRole ).toFloat();
        aStream << weiYi;

        aItem = model->item( i, 4 ); //固井质量
        QString zhiLiang = aItem->data( Qt::DisplayRole ).toString();
        aStream << zhiLiang;

        aItem = model->item( i, 5 ); //测井取样
        bool quYang = ( aItem->checkState() == Qt::Checked );
        aStream << quYang;
    }

    aFile.close();
    QMessageBox::information( this, "消息提示", "stm文件保存成功" );
}
//打开dat文件
void MainWindow::on_act_dat_open_triggered()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getOpenFileName( this, "打开一个dat文件",
                        curPath, "标准编码文件(*.dat)" );

    QFile aFile( aFileName ); //负责打开关闭文件
    if ( !( aFile.open( QIODevice::ReadOnly ) ) ) //以只读的方式打开
        return;

    QDataStream aStream( &aFile ); //数据流绑定文件
    aStream.setByteOrder( QDataStream::LittleEndian ); //设置其字节顺序
    qint16 rowCount, colCount;
    aStream.readRawData( ( char * )&rowCount, sizeof( qint16 ) ); //最多从流中读取len字节为s，并返回所读取的字节数
    aStream.readRawData( ( char * )&colCount, sizeof( qint16 ) );
    resetTable(rowCount);

    //读取表头文字,但是并不利用,因为是顺序读入读出
    char *buf;
    uint strLen;
    for ( int i = 0; i < colCount; ++i )
    {
        aStream.readBytes( buf, strLen ); //同时读取字符串长度和字符内容
        //返回用8位字符串str的第一个大小字符初始化的QString。
        QString str = QString::fromLocal8Bit( buf, strLen );
    }

    //读取数据区数据
    QStandardItem *aItem;
    qint16 ceShen;
    qreal chuiShen, fangWei, weiYi;
    QString zhiLiang;
    qint8 quYang; //1==true,0==false
    QModelIndex index;
    for ( int i = 0; i < rowCount; i++ )
    {
        aStream.readRawData((char *)&ceShen, sizeof(qint16)); //读取指定长度的字节
        index = model->index(i, 0);
        aItem = model->itemFromIndex(index);
        aItem->setData(ceShen, Qt::DisplayRole); //设置指定项中的数据

        aStream.readRawData( (char *)&chuiShen, sizeof(qreal));
        index = model->index(i, 1);
        aItem = model->itemFromIndex(index);
        aItem->setData(chuiShen, Qt::DisplayRole);

        aStream.readRawData((char *)&fangWei, sizeof(qreal));
        index = model->index(i, 2);
        aItem = model->itemFromIndex (index);
        aItem->setData(fangWei, Qt::DisplayRole);

        aStream.readRawData( (char *)&weiYi, sizeof(qreal));
        index = model->index(i, 3);
        aItem = model->itemFromIndex (index);
        aItem->setData(weiYi, Qt::DisplayRole);

        aStream.readBytes (buf, strLen);
        zhiLiang = QString::fromLocal8Bit (buf, strLen);
        index = model->index(i, 4);
        aItem = model->itemFromIndex (index) ;
        aItem->setData(zhiLiang, Qt::DisplayRole);

        aStream. readRawData( (char *)&quYang, sizeof (qint8));
        index = model->index(i, 5);
        aItem = model->itemFromIndex (index);

        if (quYang == 1)
            aItem->setCheckState(Qt::Checked);
        else
            aItem->setCheckState(Qt::Unchecked);
    }

    aFile.close();//关闭文件
    QMessageBox::information(this, "消息提示", "dat文件打开成功" );
}
//保存dat文件
void MainWindow::on_act_dat_save_triggered()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getSaveFileName(this, "保存dat文件",
                        curPath, "标准编码文件(*.dat)" );

    QFile aFile(aFileName); //负责打开文件
    if (!(aFile.open(QIODevice::WriteOnly))) //以只写的方式打开
        return;

    QDataStream aStream(&aFile);//数据流绑定文件
    aStream.setByteOrder(QDataStream::LittleEndian);//设置为小端存储

    qint16 rowCount = model->rowCount();
    qint16 colCount = model->columnCount();
    aStream.writeRawData((char *)&rowCount, sizeof(qint16)); //写入到文件中去
    aStream.writeRawData((char *)&colCount, sizeof(qint16));

    //获取表头文字
    QByteArray btArray;
    QStandardItem *aItem;
    for (int i = 0; i < model->columnCount(); ++i)
    {
        aItem = model->horizontalHeaderItem(i); //获取表头item
        QString str = aItem->text(); //获取表头文字
        btArray = str.toUtf8(); //转换为字符数组
        aStream.writeBytes(btArray, btArray.length()); //写入字符串数据
    }

    //获取表格数据区
    qint8 yes = 1, no = 0;
    for (int i = 0; i < model->rowCount(); ++i)
    {
        aItem = model->item(i, 0);
        if (aItem == nullptr) qDebug() << "null";

        qint16 ceShen = aItem->data(Qt::DisplayRole).toInt ();
        aStream.writeRawData ( (char *)&ceShen, sizeof (qint16));

        aItem = model->item(i, 1);
        qreal chuiShen = aItem->data(Qt::DisplayRole).toFloat ();
        aStream.writeRawData((char *)&chuiShen, sizeof (qreal));

        aItem = model->item(i, 2);
        qreal fangWei = aItem->data(Qt::DisplayRole).toFloat ();
        aStream.writeRawData((char *)&fangWei, sizeof (qreal));

        aItem = model->item(i, 3);
        qreal weiYi = aItem->data(Qt::DisplayRole).toFloat ();
        aStream.writeRawData((char *)&weiYi, sizeof (qreal));

        aItem = model->item(i, 4);
        QString zhiLiang = aItem->data(Qt::DisplayRole).toString();
        btArray = zhiLiang.toUtf8 ();
        aStream.writeBytes (btArray, btArray.length());//字符串的写入

        aItem = model->item(i, 5);
        bool quYang = (aItem->checkState() == Qt::Checked);

        if (quYang)
            aStream.writeRawData((char *)&yes, sizeof (qint8));
        else
            aStream.writeRawData((char *)&no, sizeof (qint8));
    }

    aFile.close();
    QMessageBox::information( this, "消息提示", "dat文件保存成功" );
}

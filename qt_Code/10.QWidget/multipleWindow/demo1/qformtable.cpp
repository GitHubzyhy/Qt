#include "qformtable.h"
#include "ui_qformtable.h"
#include "QWDialogSize.h"
#include <QStandardItemModel>
#include "QWDialogHeaders.h"

QFormTable::QFormTable(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QFormTable)
{
    ui->setupUi(this);

    theModel = new QStandardItemModel(5, ColumnCount, this); //构造二维表
    selModel = new QItemSelectionModel(theModel);

    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(selModel);

    //设置扩展模式和选择行为
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);//按住shift和ctrl
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);//设置每次选择是选择项目

    headList << "Name" << "Sex" << "Age" << "Address";
    theModel->setHorizontalHeaderLabels(headList);//设置页眉
}

QFormTable::~QFormTable()
{
    delete ui;
}

void QFormTable::on_actColRow_triggered()
{
    //设置行列
    QWDialogSize *dlg = new QWDialogSize(this); //模态对话框，用完就删除
    Qt::WindowFlags flags = dlg->windowFlags();
    dlg->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    dlg->setRowColumn(theModel->rowCount(), theModel->columnCount());

    if(dlg->exec() == QDialog::Accepted)
    {
        //这时候在自定义对话框里面spinBox的值重新设置了主窗口的行和列
        theModel->setRowCount(dlg->rowCount());
        theModel->setColumnCount(dlg->columnCount());
    }
    else
    {
        delete dlg;
        return ;
    }

    delete dlg;//释放对话框对象
}

void QFormTable::on_actTitle_triggered()
{
    //设置标题
    if(dlgSetHeaders == nullptr) //如果是第一次调用就初始化，但是不会将其删除
        dlgSetHeaders = new QWDialogHeaders(this);

    if(dlgSetHeaders->headerList().count() != theModel->columnCount())
    {
        //让表头对话框里的表头与model的列是对应的
        QStringList strList;//用来保存表头标题

        //该for循环用来初始化dlgSetHeaders对话框的列表
        for(int i = 0; i < theModel->columnCount(); ++i)
            strList.append(theModel->headerData(i, Qt::Horizontal,//将每一个表头标题都存储在strList
                                                Qt::DisplayRole).toString());

        dlgSetHeaders->setHeaderList(strList);
    }

    if(dlgSetHeaders->exec() == QDialog::Accepted)
    {
        //这时候在自定义对话框里面QListView重新设置了主窗口的表头
        QStringList strList = dlgSetHeaders->headerList();
        theModel->setHorizontalHeaderLabels(strList);
    }
}

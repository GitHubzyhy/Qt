#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtWidgets>
#include <QPrinter>
#include <QPrintDialog>
#include "orderdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setTabsClosable(true);//设置创建的标签页可以删除
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested,
            this, [ = ](int index)
    {
        ui->tabWidget->removeTab(index);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
//打开自定义对话框
void MainWindow::on_actionnew_triggered()
{
    OrderDialog dlg(this);

    if (dlg.exec() == QDialog::Accepted) //如果点的是OK 模态对话框
        createLetter(dlg.senderName(), dlg.senderAddress(), dlg.orderItems(), dlg.sendOffers());
}

//开始构造短信的内容
void MainWindow::createLetter(const QString &name, const QString &address,
                              QList<QPair<QString, int> > orderitems,
                              bool sendOffers)
{
    QTextEdit *editor = new QTextEdit(this);

    //将新创建的部件添加到选项卡窗口部件中，选项卡的名称为name，并且返回新选项卡的索引
    int tabIndex = ui->tabWidget->addTab(editor, name);
    ui->tabWidget->setCurrentIndex(tabIndex);//当前选中的标签页设置为刚刚添加的标签页，

    QTextCursor cursor(editor->textCursor());//返回当前可见游标的副本
    cursor.movePosition(QTextCursor::Start);//将光标移动到文本开头

    QTextCharFormat textFormat, boldFormat; //用于设置字符格式。
    boldFormat.setFontWeight(QFont::Bold);//设置为加粗字体

    cursor.insertText(name, boldFormat); //第二个参数是字体设置

    const QStringList lines = address.split('\n'); //通过换行符拆分，生成字符串列表
    for (const QString &line : lines)
    {
        cursor.insertBlock();//插入文本块 目的是换行
        cursor.insertText(line);
    }

    //空一行
    cursor.insertBlock();
    cursor.insertBlock();

    //设置时间
    QDate date = QDate::currentDate();
    cursor.insertText(tr("Date: %1").arg(date.toString("d MMMM yyyy")), textFormat);
    cursor.insertBlock();

    cursor.insertText(tr("请你尽快回信"), boldFormat);
    cursor.insertBlock();

    //插入表格
    QTextTableFormat orderTableFormat;//设置表格格式
    orderTableFormat.setAlignment(Qt::AlignCenter);//水平方向居中
    QTextTable *orderTable = cursor.insertTable(1, 2, orderTableFormat); //行 列 格式

    //获取QTextTable中(0, 0)位置（第一行第一列）单元格的第一个光标位置，并将其保存在cursor变量中
    cursor = orderTable->cellAt(0, 0).firstCursorPosition();
    cursor.insertText(tr("产品"), boldFormat);
    cursor = orderTable->cellAt(0, 1).firstCursorPosition();
    cursor.insertText(tr("数量"), boldFormat);

    for (int i = 0; i < orderitems.count(); ++i)//范围是有多少个表格项
    {
        OrderDialog::OrderItemType item = orderitems[i]; //函数参数里面的orderitems

        int row = orderTable->rows();//表格一共有多少行
        orderTable->insertRows(row, 1); //在当前表格最后添加一行 （index，rows）

        //在添加的这一行中设置两个单元格QString int
        cursor = orderTable->cellAt(row, 0).firstCursorPosition();
        cursor.insertText(item.first, textFormat);//在当前光标位置插入文本

        cursor = orderTable->cellAt(row, 1).firstCursorPosition();
        cursor.insertText(QString("%1").arg(item.second), textFormat);
    }

    //此时光标在表格内，要将其移出来
    cursor.movePosition(QTextCursor::End);//将光标移动到最后

    QTextTable *offersTable = cursor.insertTable(2, 2); //插入一个2*2的表格

    cursor = offersTable->cellAt(0, 1).firstCursorPosition();
    cursor.insertText(tr("我愿意收到活动产品信息"), boldFormat);
    cursor = offersTable->cellAt(1, 1).firstCursorPosition();
    cursor.insertText(tr("我不愿意收到活动产品信息"), boldFormat);

    //找到offersTable的单元格
    if (sendOffers)
        cursor = offersTable->cellAt(0, 0).firstCursorPosition();
    else
        cursor = offersTable->cellAt(0, 1).firstCursorPosition();

    //大X或者勾勾
    cursor.insertText("X", boldFormat);
}

void MainWindow::on_actionprint_triggered()//只有创建了新的标签页才能打印
{
    //获取当前选中的标签页中的小部件指针，用dynamic_cast运行时执行类型转换
    QTextEdit *editor = dynamic_cast<QTextEdit *>(ui->tabWidget->currentWidget());

    if (editor) //检查是否为空指针
    {
        QPrinter printer;//QPrinter是Qt中用于打印的设备类
        QPrintDialog dialog(&printer, this); //提供了一个标准的打印对话框，允许用户选择打印选项并执行打印操作。访问并操作 printer 对象的设置
        dialog.setWindowTitle(tr("Print Document"));//设置打印对话框的窗口标题

        if (dialog.exec() != QDialog::Accepted) //判断用户点了哪个按钮
            return;

        editor->print(&printer);//将文本编辑器中的内容打印到指定的打印设备（由 printer 对象管理）上。
    }
}

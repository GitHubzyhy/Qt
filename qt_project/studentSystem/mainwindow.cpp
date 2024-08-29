#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>//文件
#include <QRandomGenerator>//随机数
#include <QTime>//时间
#include <QMessageBox>//消息
#include <QTextStream>//文本流
#include <algorithm>//c++算法

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_ptrStuSql(nullptr)
{
    ui->setupUi(this);
    resize(1127, 480);
    ui->treeWidget->setColumnCount(1);

    QStringList l;
    l << "学生信息管理系统";
    QTreeWidgetItem *p1 = new QTreeWidgetItem( ui->treeWidget, l);
    ui->treeWidget->addTopLevelItem(p1);
    l.clear();

    l << "学生管理";
    QTreeWidgetItem *p2 = new QTreeWidgetItem( p1, l);

    l.clear();
    l << "管理员管理";
    QTreeWidgetItem *p3 = new QTreeWidgetItem( p1, l);

    p1->addChild(p2), p1->addChild(p3); //添加父子关系
    //树节点对应当前堆栈的哪个标签页
    ui->treeWidget->setCurrentItem(ui->treeWidget->topLevelItem(0)->child(0));

    initNames();//初始化样例数据的姓名。
    m_ptrStuSql = stuSql::getinstance(); //全局只有一个实例
    dataFlush();//从数据库读取数据显示在表中
    changeTheme();//初始化切换主题
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_ptrStuSql;
}

//将文件中的名字读取到m_lNames
void MainWindow::initNames()
{
    QFile fileIn(":/NamesFile/names.txt");
    if (!fileIn.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, tr("打开文件"),
                             tr("打开文件失败：") + fileIn.errorString());
        return;
    }

    //文件已经正确打开，定义文本流
    QTextStream tsIn(&fileIn);
    QString tempStr;
    while (!tsIn.atEnd()) //是否到达文本流末尾
    {
        tsIn >> tempStr;
        //判断空行
        if (tempStr.isEmpty())
        {
            tsIn.skipWhiteSpace();//跳过空白
            continue;
        }
        m_lNames << tempStr;
    }
}
//读取qss
void MainWindow::changeTheme()
{
    QFile fileIn;
    fileIn.setFileName(":/stuqss.css");
    if (!fileIn.open(QIODevice::ReadOnly)) //选择只读打开
    {
        QMessageBox::warning(this, tr("打开错误")
                             , tr("打开文件错误：") + fileIn.errorString());
        return; //不处理文件
    }

    QString strQss = fileIn.readAll();//全部读取
    m_dlgLogin.setStyleSheet(strQss);

    this->setStyleSheet(strQss); //把样式给主界面
    fileIn.close();
}
//刷新数据
void MainWindow::dataFlush()
{
    //tableWidget属性设置
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(9);//设置9列
    QStringList l;
    l << "序号" << "ID" << " 姓名" << "年龄" << "年级" << "班级" << "学号" << "电话" << " 微信";
    ui->tableWidget->setHorizontalHeaderLabels(l);//使用标签设置水平页眉标签。
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//只能选中行
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//每个选项不能编辑

    auto cnt = m_ptrStuSql->getStuCnt(); //判断有多少条数据
    ui->lb_cnt->setText(QString("学生总数：%1").arg(cnt));
    QList<StuInfo> lStudents = m_ptrStuSql->getPageStu(0, cnt); //获取第0页cnt个学生的list集合

    ui->tableWidget->setRowCount(cnt);//设置cnt行
    for (int i = 0; i < lStudents.size(); ++i)//设置表格数据
    {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(i))); //第i行第0列数字要转换为QString
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(lStudents[i].id)));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(lStudents[i].name));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(lStudents[i].age)));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(lStudents[i].grade)));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(lStudents[i].uiclass)));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(lStudents[i].studentid)));
        ui->tableWidget->setItem(i, 7, new QTableWidgetItem(lStudents[i].phone));
        ui->tableWidget->setItem(i, 8, new QTableWidgetItem(lStudents[i].wechat));
    }
}
//随机模拟数据
void MainWindow::on_btn_simulation_clicked()
{
    //制造1000条数据
    QRandomGenerator g;
    //设置随机数生成器的种子值，这会影响随机数序列的起始点。
    g.seed(QTime::currentTime().msecsSinceStartOfDay());

    QList<StuInfo> l;//用于存储生成的数据
    for (int i = 0; i < m_lNames.size(); ++i)
    {
        StuInfo info;
        info.name = m_lNames[i];
        if (i % 3)
            info.age = 16;
        else if (i % 7)
            info.age = 17;
        else if (i % 2)
            info.age = 18;

        auto grade = g.bounded(7, 10);//返回一个介于min和max之间的随机整数，包括两者。
        auto uiclass = g.bounded(1, 8);

        info.grade = grade;
        info.uiclass = uiclass;
        info.studentid = i;
        info.phone = "138";
        info.wechat = "139";

        //新行的单元格默认 NULL
        int OldCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        ui->tableWidget->setItem(OldCount, 0, new QTableWidgetItem(QString::number(OldCount))); //序号
        ui->tableWidget->setItem(OldCount, 1, new QTableWidgetItem(QString::number(OldCount + 1))); //ID
        ui->tableWidget->setItem(OldCount, 2, new QTableWidgetItem(info.name ));
        ui->tableWidget->setItem(OldCount, 3, new QTableWidgetItem(QString::number(info.age)));
        ui->tableWidget->setItem(OldCount, 4, new QTableWidgetItem(QString::number(info.grade)));
        ui->tableWidget->setItem(OldCount, 5, new QTableWidgetItem(QString::number(info.uiclass)));
        ui->tableWidget->setItem(OldCount, 6, new QTableWidgetItem(QString::number(info.studentid)));
        ui->tableWidget->setItem(OldCount, 7, new QTableWidgetItem(info.phone));
        ui->tableWidget->setItem(OldCount, 8, new QTableWidgetItem(info.wechat));

        l.append(info);
    }
    m_ptrStuSql->addStu(l);//整块读取到数据库 提高效率

    ui->lb_cnt->setText(QString("学生总数：%1").arg(ui->tableWidget->rowCount()));
    ui->tableWidget->scrollToBottom();//滚动到底部
}
//添加
void MainWindow::on_btn_add_clicked()
{
    //一个函数即当添加也当修改，通过bool参数区分
    m_dlgAddStu.setType(true);
    m_dlgAddStu.exec();//调用自定义对话框，数据已经被写入到了数据库

    int nCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(nCount);//插入一行 条目默认为空
    StuInfo info = m_dlgAddStu.getInfo(); //获取修改后的info

    ui->tableWidget->setItem(nCount, 0, new QTableWidgetItem(QString::number(nCount))); //序号
    ui->tableWidget->setItem(nCount, 1, new QTableWidgetItem(QString::number(nCount + 1))); //ID
    ui->tableWidget->setItem(nCount, 2, new QTableWidgetItem(info.name ));
    ui->tableWidget->setItem(nCount, 3, new QTableWidgetItem(QString::number(info.age)));
    ui->tableWidget->setItem(nCount, 4, new QTableWidgetItem(QString::number(info.grade)));
    ui->tableWidget->setItem(nCount, 5, new QTableWidgetItem(QString::number(info.uiclass)));
    ui->tableWidget->setItem(nCount, 6, new QTableWidgetItem(QString::number(info.studentid)));
    ui->tableWidget->setItem(nCount, 7, new QTableWidgetItem(info.phone));
    ui->tableWidget->setItem(nCount, 8, new QTableWidgetItem(info.wechat));

    ui->tableWidget->setCurrentItem(ui->tableWidget->item(ui->tableWidget->rowCount() - 1, 0));
    ui->tableWidget->scrollToBottom();//滚动到最下面
    ui->lb_cnt->setText(QString("学生总数：%1").arg(nCount + 1));
}
//清空
void MainWindow::on_btn_clear_clicked()
{
    m_ptrStuSql->clearStuTable();//清空学生所有信息
    dataFlush();//从空的数据库里加载比手动删除QTableWidget的行快
}
//删除
void MainWindow::on_btn_del_clicked()
{
    //支持删除多行，对于多行的删除，要从末尾开始删除，保证前面的行号不错乱
    QList<int> listRowIndex;//保存要删的行号
    //选中区域
    QList<QTableWidgetSelectionRange> listRanges = ui->tableWidget->selectedRanges();
    int nRangeCount = listRanges.count();
    if (nRangeCount < 1)
    {
        QMessageBox::warning(this, tr("区域删除"), "没有选中行");
        return;
    }

    //有选中区域
    for (int i = 0; i < nRangeCount; ++i)
    {
        //目前这一块矩形区域里的行计数
        int nCurRangeRowCount = listRanges[i].rowCount();
        for (int j = 0; j < nCurRangeRowCount; ++j)
        {
            //选中行序号
            int nRowIndex = listRanges[i].topRow() + j;
            if (!listRowIndex.contains(nRowIndex)) //没有重复的
                listRowIndex.append(nRowIndex);//添加到行号列表
        }
    }

    //对行号排序
    std::sort(listRowIndex.begin(), listRowIndex.end());
    //从末尾开始删除行 减少对前面条目造成影响
    int nRowIndexCount = listRowIndex.count();
    for (int i = nRowIndexCount - 1; i >= 0; --i)//先删数据库 再删行
    {
        //数据库里按照id删除
        m_ptrStuSql->delStu(ui->tableWidget->item(listRowIndex[i], 1)->text().toUInt());
        ui->tableWidget->removeRow(listRowIndex[i]);
    }
    QMessageBox::information(nullptr, "区域删除", "选中区域全部删除成功！");

    ui->lb_cnt->setText(QString("学生总数：%1").arg(ui->tableWidget->rowCount()));
}
//更新
void MainWindow::on_btn_update_clicked()
{
    StuInfo info;
    int i = ui->tableWidget->currentRow(); //获取当前哪一列
    if (i >= 0)
    {
        //从表格中拿到数据，整数要加toUInt()
        info.id = ui->tableWidget->item(i, 1)->text().toUInt();
        info.name = ui->tableWidget->item(i, 2)->text();
        info.age = ui->tableWidget->item(i, 3)->text().toUInt();
        info.grade = ui->tableWidget->item(i, 4)->text().toUInt();
        info.uiclass = ui->tableWidget->item(i, 5)->text().toUInt();
        info.studentid = ui->tableWidget->item(i, 6)->text().toUInt();
        info.phone = ui->tableWidget->item(i, 7)->text();
        info.wechat = ui->tableWidget->item(i, 8)->text();

        m_dlgAddStu.setType(false, info); //将数据显示到自定义对话框中
        m_dlgAddStu.exec();//自定义对话框按下确定后保存到数据库中

        //QTableWidget显示修改
        info = m_dlgAddStu.getInfo(); //这时候info是改变后的
        ui->tableWidget->item(i, 1)->setText(QString("%1").arg(info.id));
        ui->tableWidget->item(i, 2)->setText(info.name);
        ui->tableWidget->item(i, 3)->setText(QString("%1").arg(info.age));
        ui->tableWidget->item(i, 4)->setText(QString("%1").arg(info.grade));
        ui->tableWidget->item(i, 5)->setText(QString("%1").arg(info.uiclass));
        ui->tableWidget->item(i, 6)->setText(QString("%1").arg(info.studentid));
        ui->tableWidget->item(i, 7)->setText(info.phone);
        ui->tableWidget->item(i, 8)->setText(info.wechat);
    }
}
//搜索
void MainWindow::on_btn_search_clicked()
{
    QString strFilter = ui->le_search->text(); //获取搜索框的内容
    if (strFilter.isEmpty())
    {
        QMessageBox::information(nullptr, "警告", "名字筛选为空");
        dataFlush();//刷新下数据 复位
        return;
    }

    ui->tableWidget->clear();//会保留行数列数，只是条目没了
    ui->tableWidget->setColumnCount(9);//设置9列
    QStringList l;
    l << "序号" << "ID" << " 姓名" << "年龄" << "年级" << "班级" << "学号" << "电话" << " 微信";
    ui->tableWidget->setHorizontalHeaderLabels(l);//使用标签设置水平页眉标签。

    auto cnt = m_ptrStuSql->getStuCnt(); //判断有多少条数据
    ui->lb_cnt->setText(QString("学生总数：%1").arg(cnt));
    QList<StuInfo> lStudents = m_ptrStuSql->getPageStu(0, cnt); //获取第0页cnt个学生的list集合

    int index = 0;
    for (int i = 0; i < lStudents.size(); ++i) //表格数据的输出
    {
        if (!lStudents[i].name.contains(strFilter)) continue; //没有找到直接跳过

        ui->tableWidget->setItem(index, 0, new QTableWidgetItem(QString::number(index + 1))); //第i行第0列数字要转换为QString
        ui->tableWidget->setItem(index, 1, new QTableWidgetItem(QString::number(lStudents[i].id)));
        ui->tableWidget->setItem(index, 2, new QTableWidgetItem(lStudents[i].name));
        ui->tableWidget->setItem(index, 3, new QTableWidgetItem(QString::number(lStudents[i].age)));
        ui->tableWidget->setItem(index, 4, new QTableWidgetItem(QString::number(lStudents[i].grade)));
        ui->tableWidget->setItem(index, 5, new QTableWidgetItem(QString::number(lStudents[i].uiclass)));
        ui->tableWidget->setItem(index, 6, new QTableWidgetItem(QString::number(lStudents[i].studentid)));
        ui->tableWidget->setItem(index, 7, new QTableWidgetItem(lStudents[i].phone));
        ui->tableWidget->setItem(index, 8, new QTableWidgetItem(lStudents[i].wechat));
        index++;
    }
    ui->tableWidget->setRowCount(index);//设置设置cnt行
}

//根据QTreeWidget条目变化切换QStackWidget的页面
void MainWindow::on_treeWidget_currentItemChanged(QTreeWidgetItem *current,
        QTreeWidgetItem *previous)
{
    // 获取所选树节点的文本
    QString itemText = current->text(0);
    if (itemText == "学生管理")
        ui->stackedWidget->setCurrentIndex(1); // 假设"Page1"对应索引0
    else if (itemText == "管理员管理")
        ui->stackedWidget->setCurrentIndex(0); // 假设"Page0"对应索引1
    else
        ui->treeWidget->setCurrentItem(previous);
}
//复选框判断是否全选
void MainWindow::on_checkBox_toggled(bool checked)
{
    if (checked)
        ui->tableWidget->selectAll();//选择视图中所有的项目
    else//清空旧的选中状态
        ui->tableWidget->setCurrentItem(NULL, QItemSelectionModel::Clear);
}

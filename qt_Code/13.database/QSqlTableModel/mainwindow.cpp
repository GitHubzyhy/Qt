#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtWidgets>

//打开数据表
void MainWindow::openTable()
{
    //创建模型，打开数据库表格
    tabModel = new QSqlTableModel(this, DB);
    tabModel->setTable("employee");
    //表格模型的编辑策略设置为：必须显式调用 submitAll() 或 submitRow() 函数来提交所有修改或单独提交一行的修改。
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tabModel->setSort(tabModel->fieldIndex("EmpNo"), Qt::AscendingOrder); //按照empNo升序排列

    if (!(tabModel->select())) //用于从数据库中选择数据并将其加载到模型中
        QMessageBox::critical(this, "错误", "数据库表格打开失败" + tabModel->lastError().text());
    ui->statusbar->showMessage(QString("记录条数为：%1").arg(tabModel->rowCount()));

    changeHeader();//设置表头 默认为字段名字 英-->汉
    //model/view
    selModel = new QItemSelectionModel(tabModel, this); //将QSqlTableModel关联起来 表格视图中跟踪和管理用户的选择

    ui->tableView->setModel(tabModel);
    ui->tableView->setSelectionModel(selModel);//设置选择模型
    //隐藏照片和备注列(不适合在表格中显示)
    ui->tableView->setColumnHidden(tabModel->fieldIndex("photo"), true);
    ui->tableView->setColumnHidden(tabModel->fieldIndex("Memo"), true);

    //代理
    QStringList strList{"男", "女"};
    //这是一个自定义函数，设置为表格视图中 "Gender" 列的下拉框选项
    delegateSex.setItems(strList, false);
    //这一行代码将自定义的委托对象 delegateSex 分配给表格视图中的特定列，以控制该列的显示和编辑方式
    ui->tableView->setItemDelegateForColumn(
        tabModel->fieldIndex("Gender"), &delegateSex);

    strList.clear();//清空
    strList << "技术部" << "销售部" << "市场部";
    delegateDepart.setItems(strList, false);
    ui->tableView->setItemDelegateForColumn(
        tabModel->fieldIndex("DePartment"), &delegateDepart);

    //字段与widget的映射
    dataMapper = new QDataWidgetMapper(this);
    dataMapper->setModel(tabModel);//设置关联的数据模型
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);//设置为自动提交
    setMapper();//建立映射关系    基本都是复制粘贴

    //action的状态
    ui->actOpenDB->setEnabled(false);//打开数据库的action只能被调用一次
    ui->actRecAppend->setEnabled(true);
    ui->actRecInsert->setEnabled(true);
    ui->actRecDelete->setEnabled(true);
    ui->actScan->setEnabled(true);
    //设置两个盒子里面是否可以交互
    ui->groupBoxSort->setEnabled(true);
    ui->groupBoxFilter->setEnabled(true);

    //获取字段名更新combobox
    /*  QSqlRecord 是一个用于表示数据库记录的类，
        它可以包含一行数据，
        每一列数据都以字段名（或索引）为键存储在记录中
    */
    QSqlRecord emptyRec = tabModel->record(); //它返回一个空记录，只有字段名
    for (int i = 0; i < emptyRec.count(); ++i)
        ui->comSort->addItem(emptyRec.fieldName(i));

    connect(selModel, &QItemSelectionModel::currentChanged, //当单元格发生变化时
            this, &MainWindow::do_currentChanged);
    connect(selModel, &QItemSelectionModel::currentRowChanged, //当行发生变化时
            this, &MainWindow::do_currentRowChanged);
}
//设置表头
void MainWindow::changeHeader()
{
    tabModel->setHeaderData(tabModel->fieldIndex("EmpNo"), Qt::Horizontal, "工号");
    tabModel->setHeaderData(tabModel->fieldIndex("Name"), Qt::Horizontal, "姓名");
    tabModel->setHeaderData(tabModel->fieldIndex("Gender"), Qt::Horizontal, "性别");
    tabModel->setHeaderData(tabModel->fieldIndex("height"), Qt::Horizontal, "身高");
    tabModel->setHeaderData(tabModel->fieldIndex("Birthday"), Qt::Horizontal, "生日");
    tabModel->setHeaderData(tabModel->fieldIndex("Mobile"), Qt::Horizontal, "手机号");
    tabModel->setHeaderData(tabModel->fieldIndex("Province"), Qt::Horizontal, "省份");
    tabModel->setHeaderData(tabModel->fieldIndex("City"), Qt::Horizontal, "城市");
    tabModel->setHeaderData(tabModel->fieldIndex("Department"), Qt::Horizontal, "部门");
    tabModel->setHeaderData(tabModel->fieldIndex("Education"), Qt::Horizontal, "学历");
    tabModel->setHeaderData(tabModel->fieldIndex("Salary"), Qt::Horizontal, "工资");
    //照片和备注不适合放在表里面，后续会有代码将其注销
    // tabModel->setHeaderData(tabModel->fieldIndex("Photo"),Qt::Horizontal,"照片");
    // tabModel->setHeaderData(tabModel->fieldIndex("Memo"),Qt::Horizontal,"备注");
}
//建立映射关系
void MainWindow::setMapper()
{
    //第一个参数是控件，第二个参数是真正的字段
    dataMapper->addMapping(ui->spinBoxID, tabModel->fieldIndex("EmpNo"));
    dataMapper->addMapping(ui->leditName, tabModel->fieldIndex("Name"));
    dataMapper->addMapping(ui->Gender, tabModel->fieldIndex("Gender"));
    dataMapper->addMapping(ui->doubleSpinBoxHeight, tabModel->fieldIndex("height"));
    dataMapper->addMapping(ui->Birthday, tabModel->fieldIndex("Birthday"));
    dataMapper->addMapping(ui->leditPhone, tabModel->fieldIndex("Mobile"));
    dataMapper->addMapping(ui->BirthProvince, tabModel->fieldIndex("Province"));
    dataMapper->addMapping(ui->leditCity, tabModel->fieldIndex("City"));
    dataMapper->addMapping(ui->department, tabModel->fieldIndex("Department"));
    dataMapper->addMapping(ui->education, tabModel->fieldIndex("Education"));
    dataMapper->addMapping(ui->spinBoxSalary, tabModel->fieldIndex("Salary"));
    dataMapper->addMapping(ui->textEdit, tabModel->fieldIndex("memo"));

    dataMapper->toFirst();//让其显示第一条记录
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("demo for db");
    setWindowIcon(QIcon(":/images/student.png"));//设置图表

    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//设置为单选
    ui->tableView->setAlternatingRowColors(true);//使用交替颜色绘制背景
    ui->tableView->setStyleSheet("QTableView::item:alternate {background-color: skyblue;}");
}

MainWindow::~MainWindow()
{
    delete ui;
}
//打开数据库
void MainWindow::on_actOpenDB_triggered()
{
    //过滤器显示的描述文本和文件扩展名 返回的是文件的路径
    QString aFile = QFileDialog::getOpenFileName(
                        this,
                        "选择文件",
                        "../",
                        "SQLite数据库(*.sqlite *.db *.db3)");
    if (aFile.isEmpty())
        return;
    DB = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库驱动
    DB.setDatabaseName(aFile);//将数据库连接配置为连接到指定的数据库文件。
    if (!DB.open()) //打开数据库
        QMessageBox::warning(this, "错误", "数据库打开失败");
    else
        openTable();//自定义函数，打开数据库表格
}
//检查数据表的内容是否修改，更新按钮使能
void MainWindow::do_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);//告诉编译器参数没有使用防止出现警告
    //设置项是否可点击
    ui->actSubmit->setEnabled(tabModel->isDirty());//脏的：未提交到数据库
    ui->actRevert->setEnabled(tabModel->isDirty());
}
//行发生变化的时候，照片和备注也应该发生变化 从记录中判断是否具有数据
void MainWindow::do_currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    if (!current.isValid()) //判断模型索引是否有效
    {
        ui->labelPhoto->clear();//清空照片
        return;
    }

    // 设置项的状态
    ui->actRecDelete->setEnabled(true);
    ui->actPhoto->setEnabled(true);
    ui->actPhotoClear->setEnabled(true);

    //映射到widget
    dataMapper->setCurrentIndex(current.row());//小部件将使用索引所在行进行填充

    QSqlRecord curRec = tabModel->record(current.row()); //获取相应行的数据记录
    if (curRec.isNull("Photo")) //如果名为name的字段为空或者没有名为name的字段，则返回true;否则返回false。
        ui->labelPhoto->clear();
    else
    {
        QPixmap pic;
        pic.loadFromData(curRec.value("Photo").toByteArray());//使用指定的格式和转换标志从二进制数据加载一个像素图。
        ui->labelPhoto->setPixmap(pic.scaledToWidth(ui->labelPhoto->size().width()));//根据label的宽度进行缩放
    }

    if (curRec.isNull("memo"))
        ui->textEdit->clear();
    else
        ui->textEdit->setHtml(curRec.value("memo").toString());
}
//添加项的槽函数
void MainWindow::on_actRecAppend_triggered()
{
    QSqlRecord rec = tabModel->record(); //获取一条空记录
    rec.setValue(tabModel->fieldIndex("Gender"), "男"); //设置一个默认值
    tabModel->insertRecord(tabModel->rowCount(), rec); //插入一条空记录

    selModel->clearSelection();//清除选择模型中的选择。发出selectionChanged()。
    selModel->setCurrentIndex(tabModel->index(tabModel->rowCount() - 1, 0),
                              QItemSelectionModel::Select);//最后一个参数是选中的目的是干嘛
    ui->statusbar->showMessage(QString("记录条数为：%1").arg(tabModel->rowCount()));
}

//复习的时候看懂添加就可以不看下面这个
void MainWindow::on_actRecInsert_triggered()
{
    //插入的槽函数和添加有点类似，只是位置不一样
    QModelIndex curIndex = ui->tableView->currentIndex();

    QSqlRecord rec = tabModel->record(); //获取一条空记录
    rec.setValue(tabModel->fieldIndex("Gender"), "男"); //设置一个默认值
    tabModel->insertRecord(curIndex.row(), rec); //在指定位置 插入一条空记录

    selModel->clearSelection();//清除选择模型中的选择。发出selectionChanged()。调用connect的槽函数
    selModel->setCurrentIndex(curIndex,
                              QItemSelectionModel::Select);//最后一个参数是选中的目的是干嘛
    ui->statusbar->showMessage(QString("记录条数为：%1").arg(tabModel->rowCount()));
}

void MainWindow::on_actRecDelete_triggered()
{
    QModelIndex curIndex = ui->tableView->currentIndex(); //获取当前索引
    tabModel->removeRow(curIndex.row());//删除指定的行

    ui->statusbar->showMessage(QString("记录条数为：%1").arg(tabModel->rowCount()));
}
//设置照片
void MainWindow::on_actPhoto_triggered()
{
    //打开一个文件对话框 返回一个完整的路径
    QString aFile = QFileDialog::getOpenFileName(
                        this,
                        "选择一个照片",
                        "../",
                        "照片(*.jpg *.png *.ico)");

    QFile file(aFile);
    if (file.open(QIODevice::ReadOnly)) //已只读的方式读取
    {
        QByteArray data = file.readAll();
        file.close();//关闭文件

        QSqlRecord curRec = tabModel->record(selModel->currentIndex().row()); //使用该行的记录填充
        curRec.setValue("Photo", data);
        tabModel->setRecord(selModel->currentIndex().row(), curRec); //在某一行设置记录

        //设置图片 在界面上面显示
        QPixmap pix;
        pix.load(aFile);//aFile是文件的路径，从给定文件名的文件中加载一个像素图。如果像素图已成功加载，则返回true;否则将使像素图无效并返回false。
        ui->labelPhoto->setPixmap(pix.scaledToWidth(ui->labelPhoto->width()));

        ui->actSubmit->setEnabled(true);
        ui->actRevert->setEnabled(true);
    }
}
//清理照片的槽函数
void MainWindow::on_actPhotoClear_triggered()
{
    QSqlRecord curRec = tabModel->record(selModel->currentIndex().row());
    curRec.setNull("Photo");//将字段Photo的数据清空
    tabModel->setRecord(selModel->currentIndex().row(), curRec); //设置到表格模型中去
    ui->labelPhoto->clear();//清理照片
}
//涨工资的槽函数
void MainWindow::on_actScan_triggered()
{
    if (tabModel->rowCount() == 0)
        return;
    for (int i = 0; i < tabModel->rowCount(); ++i)
    {
        QSqlRecord aRec = tabModel->record(i); //使用该行的值填充记录
        aRec.setValue("Salary", aRec.value("Salary").toFloat() * 1.1);
        tabModel->setRecord(i, aRec); // 在第i行设置记录
    }
    //在这里全部提交
    if (tabModel->submitAll())
        QMessageBox::information(this, "消息", "涨工资执行完毕");
}
//保存
void MainWindow::on_actSubmit_triggered()
{
    bool res = tabModel->submitAll();
    if (!res)
        QMessageBox::information(this, "消息", "数据库保存失败\n" + tabModel->lastError().text());
    else
    {
        ui->actSubmit->setEnabled(false);//让其无法点击保存按钮
        ui->actRevert->setEnabled(false);
    }
    ui->statusbar->showMessage(QString("记录条数为：%1").arg(tabModel->rowCount()));
}
//取消修改
void MainWindow::on_actRevert_triggered()
{
    tabModel->revertAll();
    ui->actSubmit->setEnabled(false);//让其无法点击保存按钮
    ui->actRevert->setEnabled(false);
    ui->statusbar->showMessage(QString("记录条数为：%1").arg(tabModel->rowCount()));
}
//选择字段排序
void MainWindow::on_comSort_currentIndexChanged(int index)
{
    if (ui->rbtnUp->isChecked()) //如果勾上了
        tabModel->setSort(index, Qt::AscendingOrder); //升序
    else
        tabModel->setSort(index, Qt::DescendingOrder); //降序
    //重新把数据表里面的数据放到model里去 强制模型刷新数据
    tabModel->select();//重新检索数据库表格中的数据，然后将这些数据加载到模型中
}
//升序的单选按钮
void MainWindow::on_rbtnUp_clicked()
{
    tabModel->sort(ui->comSort->currentIndex(), Qt::AscendingOrder); //按照谁来进行升序
}
//降序的单选按钮
void MainWindow::on_rbtnDown_clicked()
{
    tabModel->sort(ui->comSort->currentIndex(), Qt::DescendingOrder); //按照谁来进行降序
}

//过滤操作 无需select()就可以刷新记录
void MainWindow::on_rbtnMan_clicked()
{
    tabModel->setFilter("Gender='男'");
    ui->statusbar->showMessage(QString("记录条数为：%1").arg(tabModel->rowCount()));
}

void MainWindow::on_rbtnWoman_clicked()
{
    tabModel->setFilter("Gender='女'");
    ui->statusbar->showMessage(QString("记录条数为：%1").arg(tabModel->rowCount()));
}

void MainWindow::on_rbtnAllDisplay_clicked()
{
    tabModel->setFilter("");
    ui->statusbar->showMessage(QString("记录条数为：%1").arg(tabModel->rowCount()));
}

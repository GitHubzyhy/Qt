#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

//调用select语句拿到数据显示在视图上面
void MainWindow::selectData()
{
    QString str = "select empNo,Name,Gender,Birthday,province,Department,"
                  "Salary from employee order by empNo";
    qryModel = new QSqlQueryModel(this); //执行SQL语句和遍历结果集的高级接口
    qryModel->setQuery(str);//重置模型并将数据提供程序设置为给定的查询。
    if (qryModel->lastError().isValid()) //判断查询是否成功
    {
        QMessageBox::critical(this, "错误", "数据库查询错误\n" +
                              qryModel->lastError().text());
        return;
    }

    //更新状态栏参数
    ui->statusbar->showMessage(QString("记录条数: %1").arg(qryModel->rowCount()));
    ui->tableView->setModel(qryModel);

    selModel = new QItemSelectionModel(qryModel, this); //与qryModel关联
    ui->tableView->setSelectionModel(selModel);
    headChange();//改变默认表格
    setMapper();
    ui->actOpenDB->setEnabled(false);//让打开数据库不能交互

    connect(selModel, &QItemSelectionModel::currentRowChanged,
            this, &MainWindow::on_currentRowChange); //一旦行号改变了就发出信号调用自己写的函数
}
//改变默认表头
void MainWindow::headChange()
{
    QSqlRecord rec = qryModel->record(); //返回字段信息
    qryModel->setHeaderData(rec.indexOf("EmpNo"), Qt::Horizontal, "工号");
    qryModel->setHeaderData(rec.indexOf("Name"), Qt::Horizontal, "姓名");
    qryModel->setHeaderData(rec.indexOf("Gender"), Qt::Horizontal, "性别");
    qryModel->setHeaderData(rec.indexOf("height"), Qt::Horizontal, "身高");
    qryModel->setHeaderData(rec.indexOf("Birthday"), Qt::Horizontal, "生日");
    qryModel->setHeaderData(rec.indexOf("Mobile"), Qt::Horizontal, "手机号");
    qryModel->setHeaderData(rec.indexOf("Province"), Qt::Horizontal, "省份");
    qryModel->setHeaderData(rec.indexOf("City"), Qt::Horizontal, "城市");
    qryModel->setHeaderData(rec.indexOf("Department"), Qt::Horizontal, "部门");
    qryModel->setHeaderData(rec.indexOf("Education"), Qt::Horizontal, "学历");
    qryModel->setHeaderData(rec.indexOf("Salary"), Qt::Horizontal, "工资");
}
//建立映射关系
void MainWindow::setMapper()
{
    dataMapper = new QDataWidgetMapper(this);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);//设置为自动提交
    dataMapper->setModel(qryModel);//与其绑定

    QSqlRecord rec = qryModel->record(); //拿到一条空的记录
    dataMapper->addMapping(ui->ID, rec.indexOf("empNo"));
    dataMapper->addMapping(ui->name, rec.indexOf("Name"));
    dataMapper->addMapping(ui->sex, rec.indexOf("Gender"));
    dataMapper->addMapping(ui->birthday, rec.indexOf("Birthday"));
    dataMapper->addMapping(ui->birthProvince, rec.indexOf("Province"));
    dataMapper->addMapping(ui->department, rec.indexOf("Department"));
    dataMapper->addMapping(ui->salary, rec.indexOf("Salary"));

    dataMapper->toFirst();//让其显示第一条记录
}
//刷新界面  此时dataMapper已经设置好了数据填充小部件
void MainWindow::refreshTableView()
{
    int index = dataMapper->currentIndex();
    QModelIndex curIndex = qryModel->index(index, 1);
    selModel->clearSelection();//清除选择模型中的选择
    //ui->tableView->selectRow(curIndex.row());//选中整行 为了好看！！！注意写在这上面

    //将模型项索引设置为当前项，并发出currentChanged()
    selModel->setCurrentIndex(curIndex, QItemSelectionModel::Select);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//打开数据库
void MainWindow::on_actOpenDB_triggered()
{
    QString aFile = QFileDialog::getOpenFileName(
                        this,
                        "选择文件",
                        "../",
                        "SQLite数据库(*.db *.db3 *.sqlite)");
    if (aFile.isEmpty()) //判断路径是否有效
        return;
    DB = QSqlDatabase::addDatabase("QSQLITE"); //添加数据库驱动
    DB.setDatabaseName(aFile);//将数据库连接配置为连接到指定的数据库文件。
    if (DB.open())
        selectData();
    else
        QMessageBox::warning(this, "error", "打开数据库失败");
}
//首记录
void MainWindow::on_actRectFirst_triggered()
{

    dataMapper->toFirst();//使用模型第一行的数据填充小部件
    refreshTableView();
}

void MainWindow::on_actRectprevious_triggered()
{
    dataMapper->toPrevious();//使用模型上一行的数据填充小部件
    refreshTableView();
}

void MainWindow::on_actRectNext_triggered()
{
    dataMapper->toNext();//使用模型下一行的数据填充小部件
    refreshTableView();
}

void MainWindow::on_actRecLast_triggered()
{
    dataMapper->toLast();//使用模型最后一行的数据填充小部件
    refreshTableView();
}
//更新照片 备注
void MainWindow::on_currentRowChange(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);//告诉编译器第二个参数用不到
    if (!current.isValid()) //如果是无效的
    {
        ui->photo->clear();
        ui->memo->clear();
        return;
    }

    dataMapper->setCurrentModelIndex(current);//设置当前映射模型索引在哪个位置
    bool first = (current.row() == 0);
    bool last = (current.row() == qryModel->rowCount() - 1);
    //设置是否可以交互
    ui->actRectFirst->setEnabled(!first);
    ui->actRectprevious->setEnabled(!first);
    ui->actRectNext->setEnabled(!last);
    ui->actRecLast->setEnabled(!last);

    //获取photo和memo(没有放入qryModel)
    int curRecNo = selModel->currentIndex().row(); //返回的是当前选中的行
    QSqlRecord curRec = qryModel->record(curRecNo); //返回当前行的记录
    int empNo = curRec.value("EmpNo").toInt(); //主键

    /*QSqlQuery 是 Qt 中用于执行 SQL 查询的类。它允许你准备和执行 SQL 查询语句，并获取查询结果。*/
    QSqlQuery query;
    if (!query.prepare("select memo,photo from employee where empno= :ID"))
    {
        // 准备sql查询，里面可以用占位符替代
        QMessageBox::critical(this, "错误", "sql语句错误: " + query.lastError().text());
        return;
    }
    query.bindValue(":ID", empNo);
    query.exec();//执行SQL查询，结果存储在对象中
    query.first();
    /*  将查询结果的游标移动到第一行（如果查询返回多行结果）。
        在多行结果的情况下，你可以使用 query.next() 来逐行迭代结果集。*/

    QVariant valuePhone = query.value("Photo");
    if (!valuePhone.isValid()) //判断数据是否是有效的
        ui->photo->clear();
    else
    {
        QByteArray data = valuePhone.toByteArray();
        //显示图片
        QPixmap pix;
        pix.loadFromData(data);
        ui->photo->setPixmap(pix.scaledToWidth(ui->photo->size().width()));
    }
    QVariant valueMemo = query.value("memo"); //获取memo的数据
    ui->memo->setHtml(valueMemo.toString());//将获取的数据写到界面中
}

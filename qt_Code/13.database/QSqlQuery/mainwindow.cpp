#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>//文件对话框
#include <QMessageBox>
#include "tdialogdata.h"

//打开数据表
void MainWindow::selectData()
{
    qryModel = new QSqlQueryModel(this);
    selModel = new QItemSelectionModel(qryModel, this); //让它与qryModel绑定
    ui->tableView->setModel(qryModel);
    ui->tableView->setSelectionModel(selModel);

    //重置模型并将数据提供程序设置为给定的查询。
    qryModel->setQuery("select empNo,Name,Gender,Birthday,Province,Department,"
                       "Salary from employee order by empno");
    //判断执行是否有错误
    if (qryModel->lastError().isValid())
    {
        QMessageBox::information(this, "error", "数据库读取表格失败!\n" + qryModel->lastError().text());
        return;
    }
    headChange();//改变表头字段名称 英文-->中文

    //设置项的是否可交互
    ui->actOpenDB->setEnabled(false);
    ui->actRecInsert->setEnabled(true);
    ui->actRecDelete->setEnabled(true);
    ui->actRecEdit->setEnabled(true);
    ui->actScan->setEnabled(true);
}
//设置表头
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
//更新记录
void MainWindow::updateRecord(int recNo)
{
    QSqlRecord curRec = qryModel->record(recNo); //通过行号获取记录 记录不全！！！
    int empNo = curRec.value("EmpNo").toInt();//工号

    QSqlQuery query;
    query.prepare("select * from employee where EmpNo=:ID");//准备要执行的sql语句
    query.bindValue(":ID", empNo); //给占位符绑定一个值
    query.exec();//执行sql语句

    query.first();//拿到执行完的第一条数据
    if (!query.isValid())
        return;
    curRec = query.record(); //完整的记录！！

    TdialogData *dataDialog = new TdialogData(this); //自定义对话框
    dataDialog->setRecord(curRec);
    if (dataDialog->exec() == QDialog::Accepted)
    {
        QSqlRecord recData = dataDialog->record(); //获取对话框里新输入的值
        query.prepare("Update employee set Name=:Name,Gender=:Gender,"
                      " Birthday=:Birthday,ProVince=:Province,Department=:Department,"
                      "Salary=:Salary,Memo=:Memo,Photo=:Photo "
                      " where EmpNo = :EmpNo"
                     );// :是占位符
        query.bindValue(":EmpNo", recData.value("EmpNo")); //将占位符设置为将占位符绑定到预处理语句中的值val。
        query.bindValue(":Name", recData .value("Name"));
        query.bindValue(":Gender", recData.value("Gender")) ;
        query.bindValue(":Birthday", recData.value("Birthday")) ;
        query.bindValue(":Province", recData.value("province"));
        query.bindValue(":Department", recData.value("Department"));
        query.bindValue(":Salary", recData.value("salary")) ;
        query.bindValue(":Memo", recData.value("Memo")) ;
        query.bindValue(":Photo", recData.value("photo")) ;

        if (!query.exec()) //如果执行不成功
            QMessageBox::critical(this, "error", "更新数据错误\n" + query.lastError().text());
        else
        {
            QSqlQuery query1 = qryModel->query();//返回的是const不能被exec()
            query1.exec();
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tableView);//设置为主窗口的中心小部件

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//让其无法编辑
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//用户可以选择整行而不是单个单元格
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//选择模式设置为单选
}

MainWindow::~MainWindow()
{
    delete ui;
}
//打开数据库
void MainWindow::on_actOpenDB_triggered()
{
    QString aFile = QFileDialog::getOpenFileName(this, "选择文件", "../", "SQLite(*.db *.sqlite *.db3)");
    if (aFile.isEmpty())
        return;

    DB = QSqlDatabase::addDatabase("QSQLITE"); //添加SQLite驱动
    DB.setDatabaseName(aFile);//将数据库连接配置为连接到指定的数据库文件。
    if (!DB.open()) //打开数据库
        QMessageBox::warning(this, "错误", "数据库打开失败");
    else
        selectData();
}
//插入记录
void MainWindow::on_actRecInsert_triggered()
{
    QSqlQuery query;
    query.exec("select * from employee where EmpNo=-1");//返回一条空的记录

    QSqlRecord curRec = query.record(); //目的是要他的字段 有字段名 值为空
    curRec.setValue("EmpNo", 1 + qryModel->rowCount()); //员工编号一次增加

    TdialogData *dataDialog = new TdialogData(this);
    dataDialog->setRecord(curRec);
    if (dataDialog->exec() == QDialog::Accepted) //判断关闭自定义对话框的时候的操作
    {
        QSqlRecord recData = dataDialog->record(); //返回自定义界面中操作结果
        query.prepare("INSERT INTO employee (EmpNo ,Name,Gender,Birthday,Province,"
                      "Department,Salary,Memo , Photo)"
                      " Values(:EmpNo,:Name,:Gender,:Birthday,:Province,"
                      " :Department,:Salary,:Memo,:Photo)"
                     );//准备要执行的SQL查询查询 :是占位符
        query.bindValue(":EmpNo", recData.value("EmpNo")); //将占位符设置为将占位符绑定到预处理语句中的值val。
        query.bindValue(":Name", recData .value("Name"));
        query.bindValue(":Gender", recData.value("Gender")) ;
        query.bindValue(":Birthday", recData.value("Birthday")) ;
        query.bindValue(":Province", recData.value("province"));
        query.bindValue(":Department", recData.value("Department"));
        query.bindValue(":Salary", recData.value("salary")) ;
        query.bindValue(":Memo", recData.value("Memo")) ;
        query.bindValue(":Photo", recData.value("photo")) ;
        if (!query.exec()) //如果执行不成功
            QMessageBox::critical(this, "error", "插入数据错误\n" + query.lastError().text());
        else
        {
            qryModel->setQuery(qryModel->query().executedQuery());//重新查询数据
        }
    }
    delete dataDialog;//防止内存泄露
}
//编辑记录
void MainWindow::on_actRecEdit_triggered()
{

    int curRecNo = selModel->currentIndex().row(); //获取当前索引的行号
    updateRecord(curRecNo);
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    updateRecord(index.row());
}
//删除记录
void MainWindow::on_actRecDelete_triggered()
{
    int curRecNo = selModel->currentIndex().row(); //找到对应的行号
    QSqlRecord curRec = qryModel->record(curRecNo); //找到对应行号的记录
    if (curRec.isEmpty())
        return;

    int empNo = curRec.value("EmpNo").toInt();
    QSqlQuery query;
    query.prepare("delete from employee where EmpNo=:ID");
    query.bindValue(":ID", empNo); //占位符替换
    if (!query.exec())
        QMessageBox::critical(this, "error", "删除错误\n" + query.lastError().text());
    else
        qryModel->setQuery(qryModel->query().lastQuery());//重新查询数据
}
//记录遍历(涨工资)
void MainWindow::on_actScan_triggered()
{
    // QSqlQuery qryUpdate;
    // qryUpdate.exec("Update employee set Salary=Salary+1000");
    // qryModel->setQuery(qryModel->query().lastQuery());//重新查询数据

    QSqlQuery qryEmpList;//员工工资信息列表
    qryEmpList.exec("select empNo,Salary from employee order by empNo");
    qryEmpList.first();//拿到执行完的第一条数据

    QSqlQuery qryUpdate; //临时 QSqlQuery
    qryUpdate.prepare("UPDATE employee SET Salary=:Salary WHERE EmpNo = :ID");
    while (qryEmpList.isValid()) //当前记录有效
    {
        int empID = qryEmpList.value("empNo").toInt();
        float salary = qryEmpList.value("Salary").toFloat(); //获取Salary
        salary = salary + 1000; //涨工资

        qryUpdate.bindValue(":ID", empID);
        qryUpdate.bindValue(":Salary", salary); //设置SQL语句参数
        qryUpdate.exec(); //执行update

        if (!qryEmpList.next()) //移动到下一条记录，并判断是否到末尾了
            break;
    }

    qryModel->setQuery(qryModel->query().lastQuery());//重新查询数据
    QMessageBox::information(this, "提示", "涨工资计算完毕",
                             QMessageBox::Ok, QMessageBox::NoButton);
}

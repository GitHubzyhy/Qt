#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QCoreApplication>
#include <QKeyEvent>
#include<QRandomGenerator>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,m_ptrStuSql(nullptr)
{
    ui->setupUi(this);

    m_dlgLogin.show();//进入登录界面
    auto f=[&]{//lambada表达式
        this->show();
    };
    //调用connect函数进行连接
    connect(&m_dlgLogin,&Page_Login::SendLoginSuccess,this,f);

    ui->treeWidget->clear();
    ui->treeWidget->setColumnCount(1);

    QStringList l;
    l<<"学生信息管理系统";
    QTreeWidgetItem *p1=new QTreeWidgetItem( ui->treeWidget,l);
    ui->treeWidget->addTopLevelItem(p1);
    l.clear();
    l<<" 学生管理";
    QTreeWidgetItem *p2=new QTreeWidgetItem( p1,l);

    l.clear();
    l<<"管理员管理";
    QTreeWidgetItem *p3=new QTreeWidgetItem( p1,l);

    p1->addChild(p2),p1->addChild(p3);//添加父子关系

    initNames();//初始化样例数据的姓名。
    m_ptrStuSql=stuSql::getinstance();//全局只有一个实例
    dataFlush();//从数据库读取数据显示在表中
    changeTheme();//初始化切换主题
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_F6)//如果按下了F6
    {
        changeTheme();
        dataFlush();
    }
}

void MainWindow::initNames()
{
    m_lNames<< "巫马淑慧";
    m_lNames<<" 可书";
    m_lNames<<" 乾刚洁";
    m_lNames<<" 劳嘉德 ";
    m_lNames<<" 图门采绿";
    m_lNames<<" 理雪兰 ";
    m_lNames<<" 芒柔怀 ";
    m_lNames<<" 褚冬灵 ";
    m_lNames<<" 沙逸馨 ";
    m_lNames<<" 甫凡儿 ";
    m_lNames<<" 良聪睿 ";
    m_lNames<<" 权景铄 ";
    m_lNames<<" 萨翔飞 ";
    m_lNames<<" 符文耀 ";
    m_lNames<<" 韩平灵 ";
    m_lNames<<" 微生芷琪";
    m_lNames<<" 吕和煦 ";
    m_lNames<<" 却梦露 ";
    m_lNames<<" 连嘉惠 ";
    m_lNames<<" 在巧兰 ";
    m_lNames<<" 程易云 ";
    m_lNames<<" 塞北晶 ";
    m_lNames<<" 终笑天 ";
    m_lNames<<" 朱高岑 ";
    m_lNames<<" 储文滨 ";
    m_lNames<<" 检紫薇 ";
    m_lNames<<" 端木春华";
    m_lNames<<" 惠婵娟 ";
    m_lNames<<" 疏清雅 ";
    m_lNames<<" 骑轶";
    m_lNames<<" 范抒";
    m_lNames<<" 夙映";
    m_lNames<<" 吉华容";
    m_lNames<<" 庚璟";
    m_lNames<<" 贲又蓝";
    m_lNames<<" 谬娜兰";
    m_lNames<<" 彭高阳";
    m_lNames<<" 宏甜恬";
    m_lNames<<" 卞慕梅";
    m_lNames<<" 杞磊";
    m_lNames<<" 安静";
    m_lNames<<" 善忆之";
    m_lNames<<" 禚悦可";
    m_lNames<<" 刚子萱";
    m_lNames<<" 利源";
    m_lNames<<" 扬秋蝶";
    m_lNames<<" 董雨信";
    m_lNames<<" 邝冷雪";
    m_lNames<<" 庄景龙";
    m_lNames<<" 才凝芙";
    m_lNames<<" 瓮菁菁";
    m_lNames<<" 迟晓莉";
    m_lNames<<" 毛兴文";
    m_lNames<<" 游雨筠";
    m_lNames<<" 艾妙松";
    m_lNames<<" 张廖昶";
    m_lNames<<" 铁元旋";
    m_lNames<<" 干瑜蓓";
    m_lNames<<" 伊鸿文";
    m_lNames<<" 喻水凡";
    m_lNames<<" 慎和豫";
    m_lNames<<" 回雅可";
    m_lNames<<" 接雅晗";
    m_lNames<<" 巫问筠";
    m_lNames<<" 乙亦绿";
    m_lNames<<" 尉迟梧";
    m_lNames<<" 丑真一";
    m_lNames<<" 莫波光";
    m_lNames<<" 裔幼荷";
    m_lNames<<" 佘斯";
    m_lNames<<" 熊梓柔";
    m_lNames<<" 虞夜雪";
    m_lNames<<" 闻人萍韵";
    m_lNames<<" 建妙颜";
    m_lNames<<" 秦又香";
    m_lNames<<" 速俨雅";
    m_lNames<<" 舜初蝶";
    m_lNames<<" 莘令梓";
    m_lNames<<" 时笑卉";
    m_lNames<<" 舒梦之";
    m_lNames<<" 卑芸若";
    m_lNames<<" 伏俊爽";
    m_lNames<<" 江春";
    m_lNames<<" 羽高邈";
    m_lNames<<" 凌夏山";
    m_lNames<<" 邬新雨";
    m_lNames<<" 束梦竹";
    m_lNames<<" 毋雅柏";
    m_lNames<<" 康乐天";
    m_lNames<<" 荤忆曼";
    m_lNames<<" 蛮凡双";
    m_lNames<<" 冒和顺";
    m_lNames<<" 道春晓";
    m_lNames<<" 隋乐蓉";
    m_lNames<<" 松海逸";
}

void MainWindow::changeTheme()
{
    QFile f;
//    auto str=QCoreApplication::applicationDirPath();
//    f.setFileName(str+"//"+"stuqss.css");
    f.setFileName(":/stuqss.css");
    f.open(QIODevice::ReadOnly);//选择只读打开
    QString strQss=f.readAll();
    m_dlgLogin.setStyleSheet(strQss);

    this->setStyleSheet(strQss); //把样式给主界面
    f.close();
}

void MainWindow::dataFlush()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(9);//设置9列
    QStringList l;
    l<<"序号"<<"ID"<<" 姓名"<<"年龄"<<"年级"<<"班级"<<"学号"<<"电话"<<" 微信";
    ui->tableWidget->setHorizontalHeaderLabels(l);//使用标签设置水平页眉标签。
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//只能选中行
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//每个选项不能编辑

    auto cnt=m_ptrStuSql->getStuCnt();//判断有多少条数据
    ui->lb_cnt->setText(QString("学生总数：%1").arg(cnt));
    QList<StuInfo> lStudents=m_ptrStuSql->getPageStu(0,cnt);//获取第0页cnt个学生的list集合


    ui->tableWidget->setRowCount(cnt);//设置cnt行
    for(int i=0;i<lStudents.size();++i)//表格数据的输出
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(i)));//第i行第0列数字要转换为QString
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(lStudents[i].id)));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(lStudents[i].name));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(lStudents[i].age)));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(lStudents[i].grade)));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(lStudents[i].uiclass)));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(QString::number(lStudents[i].studentid)));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(lStudents[i].phone));
        ui->tableWidget->setItem(i,8,new QTableWidgetItem(lStudents[i].wechat));
    }
}


void MainWindow::on_btn_simulation_clicked()
{
    //制造1000条数据
    QRandomGenerator g,c;
    g.seed(0);
    c.seed(0);

    QList<StuInfo> l;
    for(int i=0;i<m_lNames.size();++i)
    {
        auto grade= g.bounded(7,10);
        auto uiclass=g.bounded(1,8);
        StuInfo info;
        info.name=m_lNames[i];
        if(i%3)
        {
            info.age=16;
        }
        else if(i%7)
        {
            info.age=17;
        }
        else if(i%2)
        {
            info.age=18;
        }
        info.grade=grade;
        info.uiclass=uiclass;
        info.studentid=i;
        info.phone="138";
        info.wechat="139";
//        m_ptrStuSql->addStu(info);
        l.append(info);
    }
    m_ptrStuSql->addStu(l);//提高效率
    dataFlush();//重新从数据库中读取
}

void MainWindow::on_btn_add_clicked()
{
    //m_dlgAddStu.show();//显示添加界面
    m_dlgAddStu.setType(true);
    m_dlgAddStu.exec();//递归调用
    dataFlush();//重新从数据库中读取数据
}

void MainWindow::on_btn_clear_clicked()
{
    m_ptrStuSql->clearStuTable();//清空学生所有信息
    dataFlush();//重新从数据库中读取数据
}


void MainWindow::on_btn_del_clicked()
{

        int i=ui->tableWidget->currentRow();//获取当前哪一列
        if(i>=0)
        {
            int id=ui->tableWidget->item(i,1)->text().toUInt();
            m_ptrStuSql->delStu(id);
            dataFlush();//刷新下数据
            QMessageBox::information(nullptr,"信息","删除成功！");
        }


}


void MainWindow::on_btn_update_clicked()
{
    StuInfo info;
    int i=ui->tableWidget->currentRow();//获取当前哪一列
    if(i>=0)
    {
        //从表格中拿到数据，整数要加toUInt()
        info.id=ui->tableWidget->item(i,1)->text().toUInt();
        info.name=ui->tableWidget->item(i,2)->text();
        info.age=ui->tableWidget->item(i,3)->text().toUInt();
        info.grade=ui->tableWidget->item(i,4)->text().toUInt();
        info.uiclass=ui->tableWidget->item(i,5)->text().toUInt();

        info.studentid=ui->tableWidget->item(i,6)->text().toUInt();
        info.phone=ui->tableWidget->item(i,7)->text();
        info.wechat=ui->tableWidget->item(i,8)->text();

        m_dlgAddStu.setType(false,info);//去dlg_AddStu中的控件设置相应的属性，方便后续sql语句调用
        m_dlgAddStu.exec();//递归调用添加界面
    }
    dataFlush();//重新从数据库中读取数据
}


void MainWindow::on_btn_search_clicked()
{

    QString strFilter=ui->le_search->text();//获取搜索框的内容
    if(strFilter.isEmpty())
    {
        QMessageBox::information(nullptr,"警告","名字筛选为空");
        dataFlush();//复位
        return;
    }
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(9);//设置9列
    QStringList l;
    l<<"序号"<<"ID"<<" 姓名"<<"年龄"<<"年级"<<"班级"<<"学号"<<"电话"<<" 微信";
     ui->tableWidget->setHorizontalHeaderLabels(l);//使用标签设置水平页眉标签。
//    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//只能选中行
//    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//每个选项不能编辑

    auto cnt=m_ptrStuSql->getStuCnt();//判断有多少条数据
    ui->lb_cnt->setText(QString("学生总数：%1").arg(cnt));
    QList<StuInfo> lStudents=m_ptrStuSql->getPageStu(0,cnt);//获取第0页cnt个学生的list集合



    int index=0;
    for(int i=0;i<lStudents.size();++i)//表格数据的输出
    {
        if(!lStudents[i].name.contains(strFilter)) continue;//没有找到直接跳过

        ui->tableWidget->setItem(index,0,new QTableWidgetItem(QString::number(index+1)));//第i行第0列数字要转换为QString
        ui->tableWidget->setItem(index,1,new QTableWidgetItem(QString::number(lStudents[i].id)));
        ui->tableWidget->setItem(index,2,new QTableWidgetItem(lStudents[i].name));
        ui->tableWidget->setItem(index,3,new QTableWidgetItem(QString::number(lStudents[i].age)));
        ui->tableWidget->setItem(index,4,new QTableWidgetItem(QString::number(lStudents[i].grade)));
        ui->tableWidget->setItem(index,5,new QTableWidgetItem(QString::number(lStudents[i].uiclass)));
        ui->tableWidget->setItem(index,6,new QTableWidgetItem(QString::number(lStudents[i].studentid)));
        ui->tableWidget->setItem(index,7,new QTableWidgetItem(lStudents[i].phone));
        ui->tableWidget->setItem(index,8,new QTableWidgetItem(lStudents[i].wechat));
         index++;
    }
            ui->tableWidget->setRowCount(index);//设置设置cnt行
}


void MainWindow::on_exe_clicked()
{
            this->hide();
}





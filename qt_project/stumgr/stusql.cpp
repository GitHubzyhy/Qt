#include "stusql.h"
#include<QMessageBox>
#include<QCoreApplication>
#include<QSqlDatabase>
#include<QSqlQuery>

stuSql* stuSql::ptrstuSql=nullptr;//类外初始化

stuSql::stuSql(QObject *parent)
    : QObject{parent}
{
    init();

    //    StuInfo s;
    //    s.name="zyh";
    //    addStu(s);
    //    getStuCnt();
    //    QList<StuInfo> l=getPageStu(2, 3);
    //    for(auto ans:l)
    //        qDebug()<<ans.id<<" ";

    //    delStu(3);
//    StuInfo s;
//    s.id=4;
//    s.name="dd";
//    updateStuInfo(s);

    UserInfo info;
    info.username="xiaoyu";
    info.password="123456";
    info.aut="admin";

    AddUser(info);
    auto l=getAllUser();
    qDebug()<<isExit("xiaoyu");
    info.password="666";
    updateUser(info);
    delUser("xiaoyu");
}

void stuSql::init()
{

    QSqlDatabase m_db = QSqlDatabase::addDatabase("QODBC");
    m_db.setHostName("127.0.0.1");
    m_db.setPort(3306);
    m_db.setDatabaseName("Mysql"); //不是Database,记得别填错
    m_db.setUserName("root");
    m_db.setPassword("123456");
    bool ok = m_db.open();
    if (ok){
        qDebug()<<"连接成功！"<<'\n';
    }
    else {
        qDebug()<<"连接失败！"<<'\n';
    }

    //    auto str=QCoreApplication::applicationDirPath();//获取应用程序的输出目录
    //    qDebug()<<str;

}

quint32 stuSql::getStuCnt()//负责查询学生的数量
{
    QSqlQuery sql(m_db);//执行SQL语句和浏览查询的结果集的接口。
    sql.exec("select count(id) from student;");

    quint32 uiCnt=0;
    while(sql.next())
    {
        uiCnt=sql.value(0).toUInt();
    }
    return uiCnt;
}

QList<StuInfo> stuSql::getPageStu(quint32 page, quint32 uiCnt)//查询第几页学生数据
{
    QList<StuInfo> l;
    QSqlQuery sql(m_db);//执行SQL语句和浏览查询的结果集的接口。
    QString strsql=QString("select * from student order by id limit %1 offset %2;")
                         .arg(uiCnt)
                         .arg(page*uiCnt);
    sql.exec(strsql);

    StuInfo info;//存储查询出来的结果
    while(sql.next())
    {
        info.id=sql.value(0).toUInt();
        info.name=sql.value(1).toString();
        info.age=sql.value(2).toUInt();
        info.grade=sql.value(3).toUInt();
        info.uiclass=sql.value(4).toUInt();
        info.studentid=sql.value(5).toUInt();
        info.phone=sql.value(6).toString();
        info.wechat=sql.value(7).toString();

        l.push_back(info);
    }
    return l;
}

bool stuSql::addStu(StuInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql=QString("insert into student(id,name,age,grade,class,studentid,phone,wechat) values(null,'%1',%2,%3,%4,%5,'%6','%7');")
                         .arg(info.name)
                         .arg(info.age)
                         .arg(info.grade)
                         .arg(info.uiclass)
                         .arg(info.studentid)
                         .arg(info.phone)
                         .arg(info.wechat);

    return sql.exec(strSql);
}

bool stuSql::addStu(QList<StuInfo> l)
{
    QSqlQuery sql(m_db);
    m_db.transaction();//开启事务

    for(auto info:l)
    {
        QString strSql=QString("insert into student(id,name,age,grade,class,studentid,phone,wechat) values(null,'%1',%2,%3,%4,%5,'%6','%7');")
                             .arg(info.name)
                             .arg(info.age)
                             .arg(info.grade)
                             .arg(info.uiclass)
                             .arg(info.studentid)
                             .arg(info.phone)
                             .arg(info.wechat);

        sql.exec(strSql);
    }
    m_db.commit();
    return true;
}

bool stuSql::delStu(int id)
{
    QSqlQuery sql(m_db);//执行SQL语句和浏览查询的结果集的接口。

    return sql.exec(QString("delete from student where id = %1;").arg(id));
}

bool stuSql::clearStuTable()
{
    QSqlQuery sql(m_db);
    return sql.exec(QString("truncate table student;"));
}

bool stuSql::updateStuInfo(StuInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql=QString("update student set name = '%1', age=%2, grade=%3,"
                             "class=%4, studentid=%5,"
                             "phone='%6', wechat='%7' where id=%8;")
                         .arg(info.name)
                         .arg(info.age)
                         .arg(info.grade)
                         .arg(info.uiclass)
                         .arg(info.studentid)
                         .arg(info.phone)
                         .arg(info.wechat)
                         .arg(info.id);
    qDebug()<<strSql;//输出sql语句检验错误
    return sql.exec(strSql);
}

QList<UserInfo> stuSql::getAllUser()
{
    QList<UserInfo> l;
    QSqlQuery sql(m_db);

    sql.exec("select *from username");

    UserInfo info;//存储查询出来的结果
    while(sql.next())
    {
        info.username=sql.value(0).toString();
        info.password=sql.value(1).toString();
        info.aut=sql.value(2).toString();
        l.push_back(info);
    }
    return l;
}

bool stuSql::isExit(QString strUser)
{
    QSqlQuery sql(m_db);
    sql.exec(QString("select *from username where username='%1'").arg(strUser));

    return sql.next();
}

bool stuSql::updateUser(UserInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql=QString("update username set  password='%1', auth='%2'"
                             "where username='%3';")
                         .arg(info.password)
                         .arg(info.aut)
                         .arg(info.username);

    return sql.exec(strSql);
}


bool stuSql::AddUser(UserInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql=QString("insert into username(username,password,auth) values('%1','%2','%3')")
                         .arg(info.username)
                         .arg(info.password)
                         .arg(info.aut);

    return sql.exec(strSql);
}

bool stuSql::delUser(QString strUser)
{

    QSqlQuery sql(m_db);
    return sql.exec(QString("delete from username where username='%1';").arg(strUser));

}



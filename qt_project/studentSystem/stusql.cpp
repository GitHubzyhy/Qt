#include "stusql.h"
#include <QMessageBox>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>

stuSql *stuSql::ptrstuSql = nullptr; //类外初始化

stuSql::stuSql(QObject *parent)
    : QObject{parent}
{
    QSqlDatabase m_db = QSqlDatabase::addDatabase("QODBC");//添加odbc的驱动
    m_db.setHostName("127.0.0.1");
    m_db.setPort(3306);
    m_db.setDatabaseName("Mysql"); //不是Database,记得别填错
    m_db.setUserName("root");
    m_db.setPassword("123456");
    bool ok = m_db.open();
    if (ok)
        qDebug() << "连接成功！" << '\n';
    else
        qDebug() << "连接失败！" << '\n';
}
//负责查询学生的数量
quint32 stuSql::getStuCnt()
{
    QSqlQuery sql(m_db);//执行SQL语句和浏览查询的结果集的接口。
    sql.exec("select count(id) from student;");

    quint32 uiCnt = 0;
    while (sql.next())
        uiCnt = sql.value(0).toUInt();
    return uiCnt;
}
//查询第几页学生数据
QList<StuInfo> stuSql::getPageStu(quint32 page, quint32 uiCnt)
{
    QList<StuInfo> l;
    QSqlQuery sql(m_db);//执行SQL语句和浏览查询的结果集的接口。
    QString strsql = QString("select * from student order by id limit %1 offset %2;")
                     .arg(uiCnt)
                     .arg(page *uiCnt);
    sql.exec(strsql);

    StuInfo info;//存储查询出来的结果
    while (sql.next())
    {
        info.id = sql.value(0).toUInt();
        info.name = sql.value(1).toString();
        info.age = sql.value(2).toUInt();
        info.grade = sql.value(3).toUInt();
        info.uiclass = sql.value(4).toUInt();
        info.studentid = sql.value(5).toUInt();
        info.phone = sql.value(6).toString();
        info.wechat = sql.value(7).toString();

        l.push_back(info);
    }
    return l;
}
//查询所有学生
QList<UserInfo> stuSql::getAllUser()
{
    QList<UserInfo> l;
    QSqlQuery sql(m_db);

    sql.exec("select *from username");

    UserInfo info;//存储查询出来的结果
    while (sql.next())
    {
        info.username = sql.value(0).toString();
        info.password = sql.value(1).toString();
        l.push_back(info);
    }
    return l;
}
//查询用户名是否存在
bool stuSql::isExit(QString strUser)
{
    QSqlQuery sql(m_db);
    sql.exec(QString("select *from username where username='%1'").arg(strUser));

    return sql.next();
}
//添加学生
bool stuSql::addStu(StuInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("insert into student(id,name,age,grade,class,studentid,phone,wechat) values(null,'%1',%2,%3,%4,%5,'%6','%7');")
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

    for (auto info : l)
    {
        QString strSql = QString("insert into student(id,name,age,grade,class,studentid,phone,wechat) values(null,'%1',%2,%3,%4,%5,'%6','%7');")
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
//删除学生
bool stuSql::delStu(int id)
{
    QSqlQuery sql(m_db);//执行SQL语句和浏览查询的结果集的接口。

    return sql.exec(QString("delete from student where id = %1;").arg(id));
}
//清空数据表
bool stuSql::clearStuTable()
{
    QSqlQuery sql(m_db);
    return sql.exec(QString("truncate table student;"));
}
//更新
bool stuSql::updateStuInfo(StuInfo info)
{
    QSqlQuery sql(m_db);
    QString strSql = QString("update student set name = '%1', age=%2, grade=%3,"
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
    qDebug() << strSql; //输出sql语句检验错误
    return sql.exec(strSql);
}

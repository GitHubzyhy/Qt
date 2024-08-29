#ifndef STUSQL_H
#define STUSQL_H

#include <QObject>
#include <QSqlDatabase>

struct StuInfo
{
    int id;
    QString name;
    quint8 age;
    quint16 grade;
    quint16 uiclass;//班级
    quint32 studentid;//学号
    QString phone;
    QString wechat;
};
//登录人员表
struct UserInfo
{
    QString username;
    QString password;
};

class stuSql : public QObject
{
    Q_OBJECT
public:
    static stuSql *ptrstuSql;
    static stuSql *getinstance()
    {
        if (ptrstuSql == nullptr)
            ptrstuSql = new stuSql;

        return ptrstuSql;
    }
    explicit stuSql(QObject *parent = nullptr);

    //查询所有学生的数量
    quint32 getStuCnt();
    //查询第几页的学生 从第0行开始
    QList<StuInfo> getPageStu(quint32 page, quint32 uiCnt);
    //查询所有学生
    QList<UserInfo> getAllUser();
    //查询用户名是否存在
    bool isExit(QString strUser);

    //增加学生
    bool addStu(StuInfo info);
    bool addStu(QList<StuInfo> l);
    //删除学生
    bool delStu(int id);
    //清空学生表
    bool clearStuTable();
    //修改学生信息
    bool updateStuInfo(StuInfo info);

private:
    QSqlDatabase m_db;
};

#endif // STUSQL_H

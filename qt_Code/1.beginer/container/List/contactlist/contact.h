#ifndef CONTACT_H
#define CONTACT_H

#include <QString>

class QDataStream;
class Contact
{
public:
    Contact();//默认构造函数，必须有
    ~Contact();
    //带参数的构造函数
    Contact(QString strName, QString strPhone, QString strAdress);
    //复制构造函数
    Contact(const Contact &c); //必须有
    //赋值运算符函数
    Contact &operator=(const Contact &c);
    //双等号函数，用于支持列表查询函数，双等号和小于号都按姓名字符串比较
    bool operator==(const Contact &c) const;
    //友元声明，小于号函数必须用两个参数的全局函数 保证能访问类的私有变量
    friend bool operator<(const Contact &c1, const Contact &c2);

    /*  友元声明，流插入运算符和流提取运算符函数
        保证数据流输入输出时能够访问类的私有变量*/
    friend QDataStream &operator<<(QDataStream &out, const Contact &c);
    friend QDataStream &operator>>(QDataStream &in, Contact &c);

    //toString 函数方便将三个成员变量作为一行文本显示到列表控件
    QString toString();

public:
    //成员变量
    QString m_strName; //姓名
    QString m_strPhone; //电话
    QString m_strAddress;//地址
};
//全局函数：两个参数的小于号函数声明 (支持排序函数)
bool operator<( const Contact &c1, const Contact &c2 );
/*  全局：流插入运算符和流提取运算符函数本身的声明
    用于支持数据流输出和输入*/
QDataStream &operator<<(QDataStream &out, const Contact &c);
QDataStream &operator>>(QDataStream &in, const Contact &c);

#endif // CONTACT_H

#include <QCoreApplication>
#include <QDate>
#include <QTime>
#include<QList>

void Date()
{
    QDate dt1{ 2020, 4, 12 }; //用来处理日期的类
    qDebug()<<"the date is "<<dt1.toString();
    QDate dt2;//没有进行初始化
    dt2.setDate(2020,3,3);
    qDebug() << "The date is " << dt2.toString();

    QTime tm1{17, 30, 12, 55 };//用来处理时钟的类
    qDebug()<<"the time is "<<tm1.toString("hh:mm:ss.zzz");//有前导0
    QTime tm2;//没有进行初始化
    tm2.setHMS(13, 52, 45, 155);
    qDebug()<<"thie time is "<<tm2.toString("hh:mm:ss.A");
}

void current_Date()
{
    QDate cd=QDate::currentDate();//获取当前日期
    QTime ct=QTime::currentTime();//获取当前时间
    QTextStream out(stdout);
    out<<"Current date is "<<cd.toString()<<'\n';
    out<<"Current time is "<<ct.toString();

}

void format()
{
    QDate cd = QDate::currentDate();
    qDebug() << "Today is " << cd.toString();
    qDebug() << "Today is " << cd.toString(Qt::TextDate);
    qDebug() << "Today is " << cd.toString(Qt::ISODate) ;
    qDebug() << "Today is " << cd.toString(Qt::RFC2822Date);
    qDebug() << "Today is " << cd.toString("yyyy-MM-dd");
    qDebug() << "Today is " << cd.toString("yy/M/dd");
    qDebug() << "Today is " << cd.toString("d. M. yyyy");
    qDebug() << "Today is " << cd.toString("d-MMMM-yyyy");

}

void isValid()
{
    QList<QDate> dates{QDate(2020,5,11), QDate(2020, 8, 1), QDate(2020, 2, 30) };
    for(QDate res:dates)//范围for
    {
        if(res.isValid())
            qDebug() << "Date " << res.toString() << " is a valid date";
        else
            qDebug() << "Date " <<res.toString() << " is not a valid date";


    }
}

void datetime()
{
    QDateTime cdt=QDateTime::currentDateTime();

    qDebug() << "The current datetime is " << cdt.toString();
    qDebug() << "The current date is " << cdt.date().toString();
    qDebug() << "The current time is " << cdt.time().toString();

}

int main(int argc, char *argv[])
{
    //Date();
    //current_Date();
    //format();
    //isValid();
    datetime();
}

#include <QCoreApplication>

class A:public QObject
{
public:
    A(QObject *parent=nullptr):QObject(parent){qInfo()<<this<<"被构造";};//构造函数
    ~A(){qDebug()<<this<<"被销毁\n";}
};

int main(int argc, char *argv[])
{

    A objA;
    //A objACopy(objA)是不允许的，不接受拷贝构造函数
    A *pA2=new A(&objA);
    //赋值运算符也不被允许
    qDebug() << "objA2: "<<pA2;

}

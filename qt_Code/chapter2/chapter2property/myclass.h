#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
#include<QDebug>
/*

这是一个带有一个属性（Priority）的宏定义，它定义了一个Qt对象的属性。具体来说，它声明了以下内容：

属性名称为priority，类型为Priority。
读取属性值的函数为priority()，返回值为Priority类型。
设置属性值的函数为setPriority()，参数类型为Priority。
属性值发生变化时会发出一个名为priorityChanged的信号。
通常，该宏定义应该在QObject的子类中使用，用于定义该对象的一个或多个属性。这些属性可以在运行时使用，通过访问对象的属性来获取或设置其值，并在属性值更改时触发一个信号。

需要注意的是，该宏定义并不提供属性的实现。开发者需要在对象类中实现属性的读写方法（例如priority()和setPriority()函数），并在属性值更改时手动发出priorityChanged信号。
*/
class MyClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Priority priority READ priority WRITE setPriority NOTIFY priorityChanged)//定义一个qt对象的属性
    //添加关于类的介绍
    Q_CLASSINFO("author","Arxibye")//作者
    Q_CLASSINFO("Version", "3.0.0")//版本
public:
    ~MyClass(){qDebug()<<"~MyClass()析构执行";}
    enum Priority { High, Low, VeryHigh, VeryLow };
    Q_ENUM(Priority) //使枚举值作为字符串，以便在调用setProperty（）时使用
void setPriority(Priority priority) {
        m_priority = priority;
        emit priorityChanged(priority);
    }

    Priority priority() const { return m_priority; }
signals:
    void priorityChanged(MyClass::Priority);
private:
    Priority m_priority;
};

#endif // MYCLASS_H

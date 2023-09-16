#include <QCoreApplication>
#include <QList>
#include <QLocale>
#include <QCollator>
#include"book.h"
using namespace Qt;

void demo1()
{
    QList<QString> authors{"张三","李四","王五"};
    for (int i=0; i < authors.size(); ++i)
        qDebug() << authors.at(i);

    authors << "莫言" << "刘慈欣";//想容器添加两个人
    qDebug() << "***********************";

    QLocale cn(QLocale::Chinese);//用于处理与地区和语言相关的设置和操作。
    QCollator collator(cn);//是Qt框架中用于字符串比较的类

    std::sort(authors.begin(), authors.end(), collator);//按照中文规则对应的排序顺序
    qDebug() << "按拼音排序:";
    for (QString &author : authors)//范围for
        qDebug() << author;


}

void Travel()
{
    QString string = "coin, book, cup, pencil, clock, bookmark";
    QStringList items = string.split(",");//用逗号分割成一个个子串放入list

    //java风格的const迭代器
    QStringListIterator it(items);//将其初始化为list的迭代器
    while (it.hasNext())//检查迭代器是否还有下一个元素
        qDebug() << it.next().trimmed() ;//it.next()跳过一个数据项返回跳过的那个数据项。trimmed用来移除字符串两端的空白字符

    //c++风格的迭代
    QStringList::Iterator it_cpp=items.begin();
    while(it_cpp!=items.end())
        qDebug()<<(*it_cpp++).trimmed();

}

void demo_set()
{
    QTextStream out(stdout);//用于将文本输出重定向到标准输出的语句。
    QSet<QString> cols1={"yellow", "red", "blue"};
    QSet<QString> cols2={"blue","pink","orange"};
    out<<"there are "<<cols1.size()<<" values in the set"<<endl;
    cols1.insert("brown");
    out<<"there are "<<cols1.size()<<" values in the set"<<endl;

    cols1.unite(cols2);//将其合并到cols1中去
    out<<"there are "<<cols1.size()<<" values in the set"<<endl;

    for(const QString &val:cols1)
        out<<val<<" ";
    out<<endl;

    QList<QString> lcols(cols1.begin(),cols1.end());
    std::sort(lcols.begin(),lcols.end());//排序
    out<<"sort"<<endl;
    for(const QString &val:lcols)
        out<<val<<" ";
}

void demo_map()
{
    QTextStream out(stdout);//用于将文本输出重定向到标准输出的语句。
    QMap<QString,int> items={{"coins",5},{"books",3}};
    items.insert("bottles",7);

    QList<int> values=items.values();//返回的是一个QList
    out<<"values: ";
    for(int val:values)
        out<<val<<" ";
    out<<endl;

    //QList<QString> keys=items.keys();
    QList<QString> keys(items.keyBegin(),items.keyEnd());
    out<<"Keys: ";
    for(const QString &key:keys)
        out<<key<<" ";
    out<<endl;

    QMapIterator<QString,int>it(items);//java风格的迭代器
    out<<"Pairs: \n";
    while(it.hasNext())
    {
        it.next();
        out<<it.key()<<" : "<<it.value()<<endl;
    }
}

bool compareByTitle(const Book &b1,const Book &b2)
{
    return b1.getTitle() < b2.getTitle();
}

void custom_sort()
{
    QTextStream out(stdout);//用于将文本输出重定向到标准输出的语句。
    QList<Book> books={
        Book("Jack London", "The Call of the Wild"),
        Book("Leo Tolstoy", "War and Peace"),
        Book("Gustave Flaubert", "Sentimental education"),
        Book("Guy de Maupassant", "Une vie"),
        Book("William Shakespeare", "Hamlet")

    };
    std::sort(books.begin(), books.end(), compareByTitle);
    for (const Book& book : books)
        out << book.getAuthor() << ": " << book.getTitle() << endl;

}

int main(int argc, char *argv[])
{

    //demo1();
    //Travel();
    //demo_set();
    //demo_map();
    custom_sort();
}

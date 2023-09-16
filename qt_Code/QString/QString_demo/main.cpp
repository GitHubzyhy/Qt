#include <QCoreApplication>
using namespace Qt;

void Traverse()
{
    QString str1{"那里有%1朵白玫瑰，%2朵红玫瑰"};
    qDebug()<<str1.arg(5).arg(6);//用实际值代替特定控制字符

    //子字符串
    QString str2 = { "The night train" };
    qDebug()  << str2.right(5);
    qDebug()  << str2.left(9);
    qDebug()  << str2.mid(4, 5);

    QTextStream out(stdout);/*其构造函数初始化了一个输出流，目标是标准输出(stdout)。这意味着后续的输出操作将通过标准输出进行。*/
    // out.setEncoding(QStringConverter::System);/*用系统的默认编码方式进行数据的转换和处理。这样设置可以确保使用与系统环境相匹配的编码方式进行文本的输入输出操作。*/

    //三种遍历方式
    //基于范围的for循环
    QString str3={"我有一个梦想"};
    for(QChar qc:str3)
        out<<qc<<" ";
    out<<endl;

    //基于迭代器访问
    for(QChar *it=str3.begin();it!=str3.end();it++)
        out<<*it<<" ";
    out<<endl;

    //基于索引访问
    for(int i=0;i<str3.size();++i)
        out<<str3.at(i)<<" ";
    out<<endl;

}

void compare()
{
    QString a{"Rain"},b{"rain"},c{"rain\n"};
    if(QString::compare(a,b)==0) qDebug()<<"a,b相等";
    else qDebug()<<"a,b不相等";

    qDebug() << "大小写不敏感的比较结果:";
    if(QString::compare(a,b,Qt::CaseInsensitive)==0){ qDebug() << "a, b 相等";}
    else {qDebug() << "a, b 不相等";}

    if (QString::compare(b, c) == 0) { qDebug() << "b, c 相等"; }
    else {qDebug() << "b, c 不相等";}

    c.chop(1);//删除最后一个字符
    qDebug() << "删除掉换行符之后：";
    if (QString::compare(b, c) == 0)  { qDebug() << "b, c 相等"; }
            else {qDebug() << "b, c 不相等";}


}

void character_type()
{
    int digits = 0; int letters = 0; int spaces = 0; int puncts = 0; QString str { "7 white, 3 red roses." };
    for (QChar s : str) {
        if (s.isDigit()) {digits++;}
        else if (s.isLetter()) {letters++;}
        else if (s.isSpace()) {spaces++;}
        else if (s.isPunct()) {puncts++;}
    }
    qDebug() << QString("There are %1 characters").arg(str.count());
    qDebug() << QString("There are %1 letters").arg(letters);
    qDebug() << QString("There are %1 digits").arg(digits);
    qDebug() << QString("There are %1 spaces").arg(spaces);
    qDebug() << QString("There are %1 punctuation characters").arg(puncts);

}

int main(int argc, char *argv[])
{
    // Traverse();//遍历字符串
    //compare();
    character_type();

}

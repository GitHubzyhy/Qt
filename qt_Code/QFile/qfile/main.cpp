#include <QCoreApplication>
#include<QFile>
using namespace Qt;

int main(int argc, char *argv[])
{
    if (argc != 2)//检查命令行参数是不是有两个，确保用户提供了正确的文件名称作为参数
    {
        qWarning("请给出文件名称！！");
        return 1;
    }
    QString filename = argv[1];//将命令行参数中的第一个参数取出
    QFile f(filename);//QFile对象f被初始化为名为"1.txt"的文件,后续对f的操作将应用于名为"test.txt"的
    if (!f.exists()) {
        qWarning("指定的文件不存在。");
        return 1;
    }
    qDebug() << f.fileName() ;

    /*--------------------------------只读的形式-------------------------------------------------------------*/
    if(!f.open(QIODevice::ReadOnly))//已只读的方式打开
    {
        qWarning("Cant't open file for reading");
        return 1;
    }
    QTextStream in(&f);//创建输入文件流，可以在QIODevice上面操作

    while(!in.atEnd())//判断是否到达了末尾
    {
        QString line=in.readLine();//读取一行
        qDebug()<<line.trimmed();
    }
    f.close();//关闭文件
    /*--------------------------------------只写的形式------------------------------------------------------------*/
    QTextStream out{stdout};
    out.setEncoding(QStringConverter::System);//设置out的编码为系统编码

    if(f.open(QIODevice::WriteOnly))//已只打开的方式
    {
        QTextStream out(&f);
        out << "张三" << endl;
        out << "李四" << endl;
        out << "王五" << endl;

    }
    else
        qWarning("Cound not open file");

}

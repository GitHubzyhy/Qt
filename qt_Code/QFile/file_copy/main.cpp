#include <QCoreApplication>
#include<QFile>

int main(int argc, char *argv[])
{
    QTextStream out{stdout};//与标准输出绑定，让其输出到控制台中

    if(argc!=3)
    {
        qWarning("Usage:copyfile source destination");
        return 1;
    }
    QString src=argv[1];
    if(!QFile{src}.exists())//判断文件是否存在
    {
        qWarning("the source file does not exist");
        return 1;

    }
    QString dest(argv[2]);
    QFile::copy(src,dest);//复制的是引用的链接
}

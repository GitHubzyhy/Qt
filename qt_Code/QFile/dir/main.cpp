#include <QCoreApplication>
#include<QDir>//用于对目录结构及内容的访问
#include<QDebug>
#include <QDirIterator>

void filter()
{
    QDir dir;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);//选择文件不包括目录，可以指定隐藏文件，指定不选择快捷方式(symbolic:引用)
    dir.setSorting(QDir::Size | QDir::Reversed);//按照内存从小到大排序
    //返回目录中所有文件和目录的QFileInfo对象列表
    QFileInfoList list=dir.entryInfoList();
    qDebug()<<"Bytes filename: ";

    for(auto fileinfo:list)
    {
        qDebug()<<QString("%1 %2").arg(fileinfo.size(),10).arg(fileinfo.fileName());//这里是右对其
    }
}

void makedir()
{
    QDir dir;
    if(dir.mkdir("mydir"))//判断是否创建成功！
        qDebug()<<"创建成功！";
    dir.mkdir("mydir2");
    if(dir.exists())
        dir.rename("mydir2","newdir");//名字冲突直接替换

    dir.mkpath("temp/newdir");//直接创建路径
}

void travelDir()
{
    //文件夹内容
    QDir dir{QDir::current()};//用于操作当前目录
    dir.setFilter(QDir::Files | QDir::AllDirs);
    //将新的过滤器添加到现有的选项中
    dir.setFilter(dir.filter() | QDir::NoDotAndDotDot);//去除 "."  ".."   它们分别表示为当前目录、上一级目录
    //setSorting无法更改QDirIterator中元素的顺
    dir.setSorting(QDir::Size | QDir::Reversed);//按照内存大小从小到大排序

    qDebug()<<QString("Filename").leftJustified(30).append("Bytes");
    QDirIterator it(dir);
    while(it.hasNext())
    {
        QFileInfo fileinfo=it.nextFileInfo();//跨过这项，返回刚刚跨过的文件信息
        QString str=fileinfo.fileName().leftJustified(30);
        str.append(QString("%1").arg(fileinfo.size()));
        qDebug()<<str;
    }
    /*这里如果使用的是QFileInfoList 就可以使sort排序发挥作用，否则使无法发挥作用的*/
}

int main(int argc, char *argv[])
{

    //    makedir();
    if(argc!=2)
    {
        qWarning("请给出文件名称");
        return 1;
    }

    QString filename="test.txt";
    QFileInfo fileinfo{filename};//独立于系统的文件信息
    QDateTime last_read=fileinfo.lastRead();
    QDateTime last_modify=fileinfo.lastModified();//上一次是多久修改的

    qDebug()<<"Last read: "<<last_read;
    qDebug()<<"last modify: "<<last_modify;

    travelDir();
}

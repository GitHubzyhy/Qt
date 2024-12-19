#include "mainwindow.h"
#include<QTextEdit>
#include<QMimeData>
#include<QDragEnterEvent>
#include<QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    edit = new QTextEdit(this);
    setAcceptDrops(true);//允许放在这上面
    edit->setAcceptDrops(false);

    setCentralWidget(edit);//将控件放在中间

    setWindowTitle("Text Editor");
}

MainWindow::~MainWindow()
{
}

//当用户把一个对象拖动到这个窗口部件上时，就会调用这个函数
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list"))
    {
        event->acceptProposedAction();//当前控件接受拖放操作的建议动作
    }
    else
        event->ignore();
}

//当用户在窗口部件放下一个对象时，就会调用dropEvent()函数
void MainWindow::dropEvent(QDropEvent *event)
{
    //QUrl 是统一资源管理器定位符它可以表示文件路径、网络地址
    QList<QUrl> urls = event->mimeData()->urls(); //返回url列表

    if (urls.empty())
        return;

    QString fileName = urls.first().toLocalFile(); //返回本地文件的绝对路径

    if (fileName.isEmpty())
        return;

    if (ReadFile(fileName))
        setWindowTitle(QString("%1-%2").arg(fileName).arg("Drag File"));

}

bool MainWindow::ReadFile(const QString &filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::Truncate);//只读/'\n'/清空之前的内容

    if (false == file.isOpen()) return false; //直接结束函数

    QTextStream stream(&file);//将文本流和文件绑定
    edit->insertPlainText(stream.readAll());//从文件中读取放入TextEdit中
    file.flush();//将所有缓冲的数据刷新到文件中。如果成功返回true;否则返回false。
    file.close();

    return true;
}

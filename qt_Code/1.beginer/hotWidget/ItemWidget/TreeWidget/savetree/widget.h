#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class QDataStream;//数据流
class QTreeWidgetItem;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButtonAddTop_clicked();//添加顶级条目
    void on_pushButtonAddChild_clicked();//添加子条目
    void on_pushButtonEditHeader_clicked();//修改树头条目
    void on_pushButtonSaveFile_clicked();//保存文件
    void on_pushButtonClearTree_clicked();//清空树
    void on_pushButtonLoadFile_clicked();//加载文件

private:
    Ui::Widget *ui;

    QFile m_file;//文件对象，用于保存或打开
    QDataStream m_ds;//数据流对象
    //保存树的先序递归函数，自顶向下保存
    void SaveTree( QTreeWidgetItem *curItem );
    //加载树的先序递归函数，自顶向下创建树形结构
    void LoadTree( QTreeWidgetItem *curItem );

    static const int MAX_COLS = 1000;//加载时的列数限制
};
#endif // WIDGET_H

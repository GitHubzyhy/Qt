#ifndef QFORMDOC_H
#define QFORMDOC_H

#include <QWidget>

namespace Ui
{
    class QFormDoc;
}

class QFormDoc : public QWidget
{
    Q_OBJECT

public:
    explicit QFormDoc(QWidget *parent = nullptr);
    ~QFormDoc();

    void openFile();//用于打开文件
    void loadFormFile(QString &aFileName); //打开文件，并将文件内容读取plainTextEdit中
signals:
    void dialogClose();
private slots:
    void setEditFont(); //设置字体
    void textCut(); //cut
    void textCopy(); //copy
    void textPaste(); //paste
    void textUndo();//撤销上一次操作
    void textRedo();//重做编辑状态
    void connectFunction();//专门用于信号槽连接的函数

private:
    Ui::QFormDoc *ui;
};

#endif // QFORMDOC_H

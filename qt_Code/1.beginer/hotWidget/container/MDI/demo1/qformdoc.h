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
private:
    QString mCurrentFile; //当前文件名
    bool mFileOpened = false; //判断当前文件是否已打开，默认为未打开
public:
    explicit QFormDoc(QWidget *parent = nullptr);
    ~QFormDoc();

    void loadFormFile(QString &aFileName); //打开文件，并将文件内容读取plainTextEdit中
    QString currentFileName(); //返回当前文件名
    bool isFileOpened(); //判断文件是否已打开
    void setEditFont(); //设置字体
    void textCut(); //cut
    void textCopy(); //copy
    void textPaste(); //paste

private:
    Ui::QFormDoc *ui;
};

#endif // QFORMDOC_H

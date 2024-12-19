#ifndef DAL_H
#define DAL_H

#include <QDialog>

class QLabel;
class QComboBox;
class QFrame;
class QLineEdit;
class QTextEdit;
class Palette : public QDialog
{
    Q_OBJECT

public:
    Palette(QWidget *parent = nullptr);
    ~Palette();
    void createCtrlFrame();// 完成颜色选取区域的创建
    void createWidget(QLabel *&label, QComboBox *&comboBox, const QString &str); //辅助上一个函数的
    void fillColorList(QComboBox *comboBox);// 颜色选取区域 颜色下拉列表中插入颜色

    void createContentFrame();// 完成展示区域的创建

private slots:
    void showWindow();// 背景色
    void showWindowText();// 前景色
    void showButton();// 按钮背景色
    void showButtonText();//按钮前景色
    void showBase();

private:
    void (Palette::*p)() = nullptr;//函数指针，为了减少代码量

    //1. 颜色选择部分
    QFrame *ctrlFrame;
    QLabel *windowLabel;
    QComboBox *windowComboBox;
    QLabel *windowTextLabel;
    QComboBox *windowTextComboBox;
    QLabel *buttonLabel;
    QComboBox *buttonComboBox;
    QLabel *buttonTextLabel;
    QComboBox *buttonTextComboBox;
    QLabel *baseLabel;
    QComboBox *baseComboBox;

    //2. 展示部分
    QFrame *contentFrame;
    QLabel *label1;
    QComboBox *comboBox1;
    QLabel *label2;
    QLineEdit *lineEdit2;
    QTextEdit *textEdit;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

};
#endif // DAL_H

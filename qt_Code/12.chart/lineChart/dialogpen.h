#ifndef DIALOGPEN_H
#define DIALOGPEN_H

#include <QPen>
#include <QDialog>

namespace Ui
{
    class DialogPen;
}

class QPen;
class DialogPen : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPen(QWidget *parent = nullptr);
    ~DialogPen();

    QPen getpen();//通过ui界面的设置返回QPen，通常是在用户选ok后用到
    void setPen(const QPen &pen);//一般是初始化的时候用到

    static QPen getPen(QPen iniPen, bool &ok); //用类名可调用 创建本对话框，并且返回QPen
private slots:
    void on_btnColor_clicked();//设置颜色的按钮的槽函数，这里打开颜色对话框

private:
    Ui::DialogPen *ui;
    QPen m_pen;//最终返回的笔
};

#endif // DIALOGPEN_H

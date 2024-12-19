#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initControls();//初始化控件

private slots:
    void on_pushButtonEditText_clicked();
    void on_fontComboBox_currentTextChanged(const QString &arg1);
    void on_spinBoxSize_valueChanged(int arg1);
    void on_comboBoxFGColor_currentTextChanged(const QString &arg1);
    void on_comboBoxBGColor_currentTextChanged(const QString &arg1);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

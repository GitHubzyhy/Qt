#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QSpinBox;
class QLabel;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_inputSpinBox1_valueChanged(int value);
    void on_inputSpinBox2_valueChanged(int value);

private:
    QSpinBox *ui_inputSpinBox1;
    QSpinBox *ui_inputSpinBox2;
    QLabel *ui_outputWidget;
};
#endif // WIDGET_H

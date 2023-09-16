#ifndef MINUSPLUS_H
#define MINUSPLUS_H

#include <QWidget>
class QLabel;
class MinusPlus : public QWidget
{
    Q_OBJECT

public:
    MinusPlus(QWidget *parent = nullptr);
    ~MinusPlus();
public slots:
    void OnPlus();
    void OnMinus();
private:
    QLabel *lbl;

};
#endif // MINUSPLUS_H

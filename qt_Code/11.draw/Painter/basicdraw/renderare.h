#ifndef RENDERARE_H
#define RENDERARE_H

#include <QWidget>

namespace Ui {
class renderAre;
}

class renderAre : public QWidget
{
    Q_OBJECT

public:
    explicit renderAre(QWidget *parent = nullptr);
    ~renderAre();

private:
    Ui::renderAre *ui;
};

#endif // RENDERARE_H

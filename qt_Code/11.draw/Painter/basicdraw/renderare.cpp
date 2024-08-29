#include "renderare.h"
#include "ui_renderare.h"

renderAre::renderAre(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::renderAre)
{
    ui->setupUi(this);

}

renderAre::~renderAre()
{
    delete ui;
}

#include "tdialogdata.h"
#include "ui_tdialogdata.h"
#include <QFileDialog>

TdialogData::TdialogData(QWidget *parent)
    : QDialog(parent), ui(new Ui::Tdialogdata)
{
    ui->setupUi(this);
}

TdialogData::~TdialogData()
{
    delete ui;
}

QSqlRecord TdialogData::record()
{
    //除了photo都已经设置了，photo是通过界面来操作的
    m_record.setValue("empNo", ui->spinEmpno->value());
    m_record.setValue ( "Name", ui->editName->text() );
    m_record.setValue( "Gender", ui->comboSex->currentText());
    m_record.setValue( "Birthday", ui->editBirth->date());

    m_record.setValue("Province", ui->comboProvince->currentText());
    m_record.setValue( "Department", ui->comboDepart->currentText());

    m_record. setValue ( "Salary", ui->spinSalary->value());
    m_record.setValue ( "Memo", ui->editMemo->toPlainText());

    return m_record;
}

void TdialogData::setRecord(const QSqlRecord &newRecord)
{
    m_record = newRecord;
    ui->spinEmpno->setEnabled(false);//静用这个小部件
    setWindowTitle("Data 对话框");

    //把值设置到屏幕上去
    ui->spinEmpno->setValue(newRecord.value("empNo").toInt());
    ui->editName->setText(newRecord.value("Name").toString());
    ui->comboSex->setCurrentText(newRecord.value("Gender").toString());
    ui->editBirth->setDate(newRecord.value("Birthday").toDate());
    ui->comboProvince->setCurrentText(newRecord.value("province").toString());
    ui->comboDepart->setCurrentText(newRecord.value("Department").toString());
    ui->spinSalary->setValue(newRecord.value("Salary").toInt());
    ui->editMemo->setPlainText(newRecord.value("Memo").toString());

    QVariant va = newRecord.value("Photo");
    if (va.isValid()) //有数据
    {
        QPixmap pic;
        pic.loadFromData(va.toByteArray());//使用指定的格式和转换标志从二进制数据加载一个像素图。
        ui->labelPhoto->setPixmap(pic.scaledToWidth(ui->labelPhoto->size().width()));//根据宽度进行缩放
    }
    else
        ui->labelPhoto->clear();
}

void TdialogData::on_btnSetPhoto_clicked()
{
    //设置照片
    QString aFile = QFileDialog::getOpenFileName(
                        this,
                        "选择图片文件",
                        "/home",
                        "照片(*.jpg *.png )");
    if (aFile.isEmpty())
        return;
    QFile *file = new QFile(aFile);
    if (!file->open(QIODevice::ReadOnly)) //已只读的方式打开
        return;

    QByteArray data = file->readAll(); //读取数据
    file->close();//关闭文件

    m_record.setValue("Photo", data); //更新下
    //放到label里面去
    QPixmap pic;
    pic.loadFromData(data);
    ui->labelPhoto->setPixmap(pic.scaledToWidth(ui->labelPhoto->size().width()));
}

void TdialogData::on_btnClearPhoto_clicked()
{
    //清除照片
    m_record.setNull("Photo");
    ui->labelPhoto->clear();
}

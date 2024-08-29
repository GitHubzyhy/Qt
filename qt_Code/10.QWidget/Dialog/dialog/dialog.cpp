#include "dialog.h"
#include "./ui_dialog.h"
#include<QtWidgets>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle("Qt的标准对话框");
    setMinimumWidth(420);//不建议设置在ui文件

    ui->toolBox->setItemText(0, "输入对话框");
    ui->toolBox->setItemText(1, "颜色对话框");
    ui->toolBox->setItemText(2, "字体对话框");
    ui->toolBox->setItemText(3, "文件对话框");
    ui->toolBox->setItemText(4, "消息对话框");
    //让打开第0个就为显示状态
    ui->toolBox->setCurrentIndex(0);

    errMsg = new QErrorMessage(this);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_btnInputInt_clicked()
{
    //整数对话框
    bool ok = false;
    int val = 15, min = 0, max = 100, stp = 1;
    int i = QInputDialog::getInt(this, "QInputDialog::getInt(): ", "百分比",
                                 val, min, max, stp, &ok);

    if(ok)//断用户按下的是ok还是cancle
        ui->editInputInt->setText(QString::number(i) + "%");
}

void Dialog::on_btnInputDouble_clicked()
{
    //浮点数对话框
    bool ok;
    qreal val = 37.56, min = 0.0, max = 100.0, stp = 1;
    int decimals = 2;
    double d = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"),
                                       "金额:", val, min, max, decimals, &ok, Qt::WindowFlags(), stp);

    if (ok)
        ui->editInputDouble->setText("¥" + QString::number(d));

}

void Dialog::on_btnInputItem_clicked()
{
    QStringList items;
    items << "春" << "夏" << "秋" << "冬";

    bool ok;
    int current = 0;
    bool editable = true;
    QString item = QInputDialog::getItem(this, tr("QInputDialog::getItem(): "),
                                         tr("季节: "), items, current, editable, &ok);

    if (ok && !item.isEmpty())
        ui->editInputItem->setText(item);

}

void Dialog::on_btnInputText_clicked()
{
    bool ok;
    //enum EchoMode { Normal, NoEcho, Password, PasswordEchoOnEdit };
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("用户名:"), QLineEdit::Normal, QDir::home().dirName(), &ok);

    if (ok && !text.isEmpty())
        ui->editInputText->setText(text);

}

void Dialog::on_btnInputMultiLine_clicked()
{
    bool ok;
    QString text = QInputDialog::getMultiLineText(this,
                   tr("QInputDialog::getMultiLineText()"), tr("地址:"),
                   "John Doe\nFreedom Street", &ok);

    if (ok && !text.isEmpty())
        ui->editInputMultiline->setText(text);

}

void Dialog::on_btnColor_clicked()
{
    QColorDialog::ColorDialogOptions options;//是一个枚举类型,配置颜色对话框的选项

    if(ui->active->isChecked())
        options |= QColorDialog::DontUseNativeDialog;

    if(ui->alpha->isChecked())
        options |= QColorDialog::ShowAlphaChannel;

    if(ui->noBtn->isChecked())
        options |= QColorDialog::NoButtons;//将选项合并到options中

    //打开一个颜色对话框
    const QColor color = QColorDialog::getColor(Qt::green, this, "选择颜色", options);

    if (color.isValid())
    {
        ui->labelColor->setText(color.name());
        ui->labelColor->setPalette(QPalette(color));
        ui->labelColor->setAutoFillBackground(true);
    }
}

void Dialog::on_btnFont_clicked()
{
    QFontDialog::FontDialogOptions options;//配置字体对话框的选项

    if(ui->checkBoxFontMonospaced->isChecked())
        options |= QFontDialog::MonospacedFonts;

    if(ui->checkBoxFontScalable->isChecked())
        options |= QFontDialog::ScalableFonts;

    if(ui->checkBoxFontNoScalable->isChecked())
        options |= QFontDialog::NonScalableFonts;

    if(ui->checkBoxFontNoButton->isChecked())
        options |= QFontDialog::NoButtons;

    if(ui->checkBoxFontNotNative->isChecked())
        options |= QFontDialog::DontUseNativeDialog;

    if(ui->checkBoxFontProportional->isChecked())
        options |= QFontDialog::ProportionalFonts;

    const QString &description = ui->labelFont->text();
    QFont defaultFont;

    if(!description.isEmpty()) defaultFont.fromString(description);//解析字体信息设置为默认字体

    bool ok;
    //打开一个字体对话框，允许用户选择字体
    QFont font = QFontDialog::getFont(&ok, defaultFont, this, "选择字体", options);

    if (ok)
    {
        ui->labelFont->setText(font.key());
        ui->labelFont->setFont(font);
    }

}

void Dialog::on_dir_clicked()
{
    QFileDialog::Options options;
    options |= QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;

    QString directory = QFileDialog::getExistingDirectory(
                            this, "QFileDialog::getExistingDirectory()", ui->labeldir->text(), options);

    if (!directory.isEmpty()) ui->labeldir->setText(directory);

}

void Dialog::on_filename_clicked()
{
    const QFileDialog::Options options;
    QString selectedFilter;//选择的过滤器，可以调试的时候打印出来
    //打开一个文件选择对话框
    QString fileName = QFileDialog::getOpenFileName(//会返回路径
                           this, "QFileDialog::getOpenFileName()", ui->labeldir->text(),
                           "All Files (*);;Text Files (*.txt);;Images (*.png *.xpm *.jpg)",
                           &selectedFilter, options);

    if (!fileName.isEmpty())
        ui->labelfilename->setText(fileName);
}

void Dialog::on_filenames_clicked()
{
    const QFileDialog::Options options;
    QString selectedFilter;

    QStringList files = QFileDialog::getOpenFileNames(//返回的是一个集合
                            ui->toolBox, tr("QFileDialog::getOpenFileNames()"),
                            QDir::currentPath(), tr("All Files (*);;Text Files (*.txt)"),
                            &selectedFilter, options);

    //用逗号一个个隔开
    if (files.count()) ui->labelfilenames->setText(QString("[%1]").arg(files.join(", ")));

}

void Dialog::on_save_clicked()
{
    const QFileDialog::Options options;
    QString selectedFilter;
    QString fileName = QFileDialog::getSaveFileName(
                           this, tr("QFileDialog::getSaveFileName()"),
                           ui->labelsave->text(), tr("All Files (*);;Text Files (*.txt)"),
                           &selectedFilter, options);

    if (!fileName.isEmpty()) ui->labelsave->setText(fileName);

}

void Dialog::on_btncritical_clicked()
{
    QMessageBox::StandardButton reply;//存储用户对对话框的响应结果。
    //关键信息对话框
    reply = QMessageBox::critical(this, tr("QMessageBox::critical()"), "MESSAGE",
                                  QMessageBox::Abort | QMessageBox::Retry | QMessageBox::Ignore);

    if (reply == QMessageBox::Abort)
        ui->labelcritical->setText(tr("Abort"));//终止
    else if (reply == QMessageBox::Retry)
        ui->labelcritical->setText(tr("Retry"));//重试
    else
        ui->labelcritical->setText(tr("Ignore"));//忽略

}

void Dialog::on_btninfo_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::information(this, tr("QMessageBox::information()"), "MESSAGE");

    if (reply == QMessageBox::Ok)
        ui->labelinfo->setText(tr("OK"));

}

void Dialog::on_btnques_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("QMessageBox::question()"), "MESSAGE",
                                  QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    if (reply == QMessageBox::Yes)
        ui->labelques->setText(tr("Yes"));
    else if (reply == QMessageBox::No)
        ui->labelques->setText(tr("No"));
    else
        ui->labelques->setText(tr("Cancel"));

}

void Dialog::on_btnwar_clicked()
{
    //这种调用构造函数的方式更为灵活
    QMessageBox msgBox(QMessageBox::Warning, tr("QMessageBox::warning()"),
                       "MESSAGE", { }, this);

    msgBox.setDetailedText("MESSAGE_DETAILS"); //显示一些细节
    msgBox.addButton(tr("Save &Again"), QMessageBox::AcceptRole);//插入相应的按钮
    msgBox.addButton(tr("&Continue"), QMessageBox::RejectRole);

    if (msgBox.exec() == QMessageBox::AcceptRole) //判断执行的结果
        ui->labelwar->setText(tr("Save Again"));
    else
        ui->labelwar->setText(tr("Continue"));

}

void Dialog::on_btnshow_clicked()
{
    errMsg->showMessage(tr("Message"));//显示一串错误信息
    ui->labelshow->setText(tr("Message"));
}

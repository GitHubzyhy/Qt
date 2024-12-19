#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class QErrorMessage;
class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_btnInputInt_clicked();

    void on_btnInputDouble_clicked();

    void on_btnInputItem_clicked();

    void on_btnInputText_clicked();

    void on_btnInputMultiLine_clicked();

    void on_btnColor_clicked();

    void on_btnFont_clicked();

    void on_dir_clicked();

    void on_filename_clicked();

    void on_filenames_clicked();

    void on_save_clicked();

    void on_btncritical_clicked();

    void on_btninfo_clicked();

    void on_btnques_clicked();

    void on_btnwar_clicked();

    void on_btnshow_clicked();

private:
    Ui::Dialog *ui;
    QErrorMessage *errMsg;
};
#endif // DIALOG_H

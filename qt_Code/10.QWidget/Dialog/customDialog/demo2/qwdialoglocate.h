#ifndef QWDIALOGLOCATE_H
#define QWDIALOGLOCATE_H

#include <QDialog>

namespace Ui
{
    class QWDialogLocate;
}

class QWDialogLocate : public QDialog
{
    Q_OBJECT

public:
    explicit QWDialogLocate(QWidget *parent = nullptr);
    ~QWDialogLocate();

    //用于设置该对话框中两个spinBox组件可以显示的最大值
    void setSpinRange(int rowCount, int colCount);
    //根据当前选择的行，列来设置两个spinBox组件显示的值
    void setSpinValue(int rowNo, int colNo);

private slots:
    void on_btnSetText_clicked();//设置文字

private:
    Ui::QWDialogLocate *ui;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // QWDIALOGLOCATE_H

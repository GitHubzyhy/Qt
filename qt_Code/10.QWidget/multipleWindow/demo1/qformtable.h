#ifndef QFORMTABLE_H
#define QFORMTABLE_H

#include <QMainWindow>
#define ColumnCount 4//QTableView固定4列

namespace Ui
{
    class QFormTable;
}

class QStandardItemModel;
class QItemSelectionModel;
class QWDialogHeaders;
class QFormTable : public QMainWindow
{
    Q_OBJECT

public:
    explicit QFormTable(QWidget *parent = nullptr);
    ~QFormTable();

private slots:
    void on_actColRow_triggered();//设置行列

    void on_actTitle_triggered();//设置标题

private:
    Ui::QFormTable *ui;
    QStandardItemModel *theModel;
    QItemSelectionModel *selModel;
    QStringList headList;//存放表头数据

    QWDialogHeaders *dlgSetHeaders = nullptr;//设置标题的对话框
};

#endif // QFORMTABLE_H

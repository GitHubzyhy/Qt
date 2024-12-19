#ifndef INTSPINDELEGATE_H
#define INTSPINDELEGATE_H

#include <QStyledItemDelegate>

class IntSpinDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit IntSpinDelegate(QObject *parent = nullptr);

    // QAbstractItemDelegate interface
public:

    //创建用于编辑模型数据的widget组件，如QSpinBox,QComboBox
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    //从数据模型获取数据，供widget组件进行编辑
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    //将widget上的数据更新到数据模型
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    //用于给widget组件设置一个合适的大小。
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // INTSPINDELEGATE_H

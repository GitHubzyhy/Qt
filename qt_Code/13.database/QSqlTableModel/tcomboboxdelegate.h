#ifndef TCOMBOBOXDELEGATE_H
#define TCOMBOBOXDELEGATE_H

#include <QStyledItemDelegate>

class TComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
private:
    QStringList m_itemList;//选择列表
    bool m_editable;//是否可以编辑
public:
    explicit TComboBoxDelegate(QObject *parent = nullptr);

    //自定义函数，初始化设置列表内容，是否可以编辑
    void setItems(QStringList items, bool editablel);

    //自定义代理必须重新实现以下四个函数-----固定的
    // QAbstractItemDelegate interface
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // TCOMBOBOXDELEGATE_H

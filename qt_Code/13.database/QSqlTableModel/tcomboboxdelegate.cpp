#include "tcomboboxdelegate.h"
#include <QComboBox>

TComboBoxDelegate::TComboBoxDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{

}

void TComboBoxDelegate::setItems(QStringList items, bool editablel)
{
    //初始化设置列表内容
    this->m_itemList = items;
    this->m_editable = editablel;
}

QWidget *TComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //创建用于编辑模型数据的widget组件
    Q_UNUSED(option);
    Q_UNUSED(index);

    QComboBox *editor = new QComboBox(parent);
    editor->setEditable(this->m_editable);//设置是否可以编辑
    editor->addItems(this->m_itemList);

    return editor;
}

void TComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //从数据模型获取数据，供widget组件进行编辑
    QString str = index.model()->data(index, Qt::EditRole).toString();

    QComboBox *comboBox = static_cast<QComboBox *>(editor);
    comboBox->setCurrentText(str);
}

void TComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    //将widget上的数据更新到数据模型
    QComboBox *comboBox = static_cast<QComboBox *>(editor);
    QString str = comboBox->currentText();
    model->setData(index, str, Qt::EditRole); //将文本数据进行更新
}

void TComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //用于给widget组件设置一个合适的大小
    editor->setGeometry(option.rect);
}

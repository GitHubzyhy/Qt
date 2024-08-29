#include "intspindelegate.h"
#include<QtWidgets>

IntSpinDelegate::IntSpinDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{

}

//创建用于编辑模型数据的widget组件，如QSpinBox,QComboBox
QWidget *IntSpinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSpinBox *spinbox=new QSpinBox(parent);
    spinbox->setMinimum(0);
    spinbox->setMaximum(200);
    return spinbox;
}

//从数据模型获取数据，供widget组件进行编辑 。
void IntSpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //从数据模型获取数据，显示到代理组件中
    //获取数据模型的模型索引指向的单元数据
    int value=index.model()->data(index,Qt::EditRole).toInt();
    QSpinBox *spinbox=static_cast<QSpinBox *>(editor);//将通用的QWidget指针转换为QSpinBox
    spinbox->setValue(value);//设置编辑器的数值
}

//将widget上的数据更新到数据模型
void IntSpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    //将代理组件的数据，保存到数据模型中
    QSpinBox *spinbox=static_cast<QSpinBox *>(editor);
    spinbox->interpretText();//解释数据，如果数据被修改就发出信号
    int value=spinbox->value();//获取spinBox的值
    model->setData(index,value,Qt::EditRole);//更新到数据模型

}

//用于给widget组件设置一个合适的大小
void IntSpinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);//编辑器的几何属性设置为这个矩形

}

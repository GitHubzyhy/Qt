#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

//网络协议头一般都用 1 字节对齐
#pragma pack(1)

//UDP 头部和报文
struct UDPPacker
{
    quint16 m_srcPort; //源端口
    quint16 m_dstPort; //目的端口
    quint16 m_length; //UDP头部和报文总长度
    quint16 m_checksum; //校验和（不是强制要求）
    QByteArray m_data; //报文内容

    //友元声明，一对用于支持QDataStream 输入输出的函数
    friend QDataStream &operator<<(QDataStream &stream, const UDPPacker &udp);
    friend QDataStream &operator>>(QDataStream &stream, UDPPacker &udp);
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButtonAddUDP_clicked();//添加UDP包

    void on_pushButtonDelUDP_clicked();//删除UDP包

    void on_pushButtonSave_clicked();//保存UDP包

    void on_pushButtonLoad_clicked();//加载UDP包

    void on_listWidget_currentRowChanged(int currentRow);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

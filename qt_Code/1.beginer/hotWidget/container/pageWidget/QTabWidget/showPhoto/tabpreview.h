#ifndef TABPREVIEW_H
#define TABPREVIEW_H

#include <QWidget>
#include <QButtonGroup>

namespace Ui
{
    class TabPreview;
}

class TabPreview : public QWidget
{
    Q_OBJECT

public:
    explicit TabPreview(QWidget *parent = nullptr);
    ~TabPreview();

    //初始化控件
    void InitControls();

public slots://主页面更新文件名，并处理预览界面的更新。
    void onFileNameChanged(const QString &fileName);

private:
    Ui::TabPreview *ui;

    QString m_strFileName;//保存文件名
    QButtonGroup m_buttonGroup;//按钮分组对象
    QPixmap m_image;//保存预览图像
};

#endif // TABPREVIEW_H

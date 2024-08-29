#include "qwbateryplugin.h"
#include "qwbatery.h"

#include <QtPlugin>

QwBateryPlugin::QwBateryPlugin(QObject *parent)
    : QObject(parent)
{}

void QwBateryPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}
//是否初始化
bool QwBateryPlugin::isInitialized() const
{
    return m_initialized;
}
//返回自定义Widget组件的实例
QWidget *QwBateryPlugin::createWidget(QWidget *parent)
{
    return new QwBatery(parent);
}
//自定义Widget组件类的名称
QString QwBateryPlugin::name() const
{
    return QLatin1String("QwBatery");
}
//在组件面板中所属分组名称
QString QwBateryPlugin::group() const
{
    return QLatin1String("My Widget");
}
//图标文件名
QIcon QwBateryPlugin::icon() const
{
    return QIcon(QLatin1String(":/file.png"));
}
//toolTip信息
QString QwBateryPlugin::toolTip() const
{
    return QLatin1String("");
}
//whatsThis 信息
QString QwBateryPlugin::whatsThis() const
{
    return QLatin1String("");
}
//是否作为容器， false表示该组件上不允许再放其他组件
bool QwBateryPlugin::isContainer() const
{
    return false;
}
//XML文件描述信息
QString QwBateryPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="QwBatery" name="qwBatery">
</widget>)");
}
//包含文件名
QString QwBateryPlugin::includeFile() const
{
    return QLatin1String("qwbatery.h");
}

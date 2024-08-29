#ifndef WeatherTool_H
#define WeatherTool_H

#include <QString>
#include <QMap>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QMessageBox>

/*  这个文件主要是获得city和cityCode的对应关系
    通过一个给定的json文件实现这一需求*/
class WeatherTool
{
public:
    WeatherTool();

    //通过这一个静态方法可以用城市名称获得城市编码
    static QString getCityCode(QString cityName)
    {
        //当这个静态函数执行过一次后，就可以直接返回城市编码(提高效率)
        if (!citycode.isEmpty())
        {
            if ( !cityName.isEmpty() )//模糊匹配
            {
                QMap<QString, QString>::const_iterator i = citycode.constBegin();
                while (i != citycode.constEnd())
                {

                    if (i.key().contains(cityName))
                    {
                        qDebug() << i.value();
                        return i.value();
                    }
                    ++i;
                }
            }
            return "";
        }

        QFile fileIn(":/citycode-2019-08-23.json");
        if (!fileIn.open(QIODevice::ReadOnly))
        {
            QMessageBox::warning(nullptr, QStringLiteral("打开错误")
                                 , QStringLiteral("打开文件错误：") + fileIn.errorString());
            return "";
        }

        //在已经知道json格式下写这一段代码
        QJsonDocument doc = QJsonDocument::fromJson(fileIn.readAll());
        QJsonArray rootArr = doc.array();
        for (int i = 0; i < rootArr.size(); ++i)
        {
            QJsonObject obj = rootArr[i].toObject(); //获取数组里面的json对象
            citycode.insert(obj.value("city_name").toString(), obj.value("city_code").toString());
        }
        fileIn.close();
        return citycode[cityName];
    }

private:
    static QMap<QString, QString> citycode; //城市，编码
};

QMap<QString, QString> WeatherTool::citycode{};//静态成员变量要在类外进行初始化

#endif // WeatherTool_H

#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QString>

class Today
{
public:
    Today()
    {
        date = "2024-08-11";
        city = "重庆";

        ganmao = "感冒指数";

        wendu = 0;
        shidu = "0%";
        pm25 = 0;
        quality = "无数据";

        type = "多云";

        fl = "2级";
        fx = "南风";

        high = 30;
        low = 18;
    }

    QString date;//日期
    QString city;//城市

    QString ganmao;//感冒指数

    int wendu;//温度
    QString shidu;//湿度
    int pm25;
    QString quality;//空气质量

    QString type;//天气类型(多云，小雨)

    QString fx;//风向
    QString fl;//风力

    int high;//最高温度
    int low;//最低温度
};

class Day
{
public:
    Day()
    {
        date = "2024-08-11";
        week = "周天";

        type = "多云";

        high = 0;
        low = 0;

        fx = "南风";
        fl = "2级";

        aqi = 0;
    }

    QString date;//日期
    QString week;//星期几

    QString type;//天气类型(多云，小雨)

    int high;//最高温
    int low;//最低温

    QString fx;//风向
    QString fl;//风力

    int aqi;//空气质量(优，良，轻度，中度，重度，严重)
};

#endif // WEATHERDATA_H

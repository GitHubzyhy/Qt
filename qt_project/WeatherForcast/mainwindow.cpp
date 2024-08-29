#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QContextMenuEvent>//右键菜单事件
#include <QMenu>//菜单
#include <QNetworkAccessManager>//协助网络操作
#include <QNetworkReply>//网络请求的响应
#include <QLabel>
#include "weathertool.h"//城市名称->城市编码
#include <QPainter>

// 温度曲线相关的宏
#define INCREMENT     3   // 温度每升高/降低1度，y轴坐标的增量
#define POINT_RADIUS  3   // 曲线描点的大小
#define TEXT_OFFSET_X 12  // 温度文本相对于点的偏移
#define TEXT_OFFSET_Y 10  // 温度文本相对于点的偏移

using Qt::endl;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint); // 无边框
    setFixedSize(width(), height()); // 固定窗口大小

    mExitMenu = new QMenu(this);
    mExitAct = new QAction("退出", this);
    mExitAct->setIcon(QIcon(":/res/close.png"));

    mExitMenu->addAction(mExitAct);//将菜单项添加到菜单里
    connect(mExitAct, &QAction::triggered, this, [ = ]()
    {
        qApp->exit(0);//退出整个程序
    });

    // 将控件放到数组里面，方便使用循环进行处理
    // 星期和日期
    mWeekList << ui->lblWeek0 << ui->lblWeek1 << ui->lblWeek2 << ui->lblWeek3 << ui->lblWeek4 << ui->lblWeek5;
    mDateList << ui->lblDate0 << ui->lblDate1 << ui->lblDate2 << ui->lblDate3 << ui->lblDate4 << ui->lblDate5;

    // 天气和天气图标
    mTypeList << ui->lblType0 << ui->lblType1 << ui->lblType2 << ui->lblType3 << ui->lblType4 << ui->lblType5;
    mTypeIconList << ui->lblTypeIcon0 << ui->lblTypeIcon1 << ui->lblTypeIcon2 << ui->lblTypeIcon3 << ui->lblTypeIcon4 << ui->lblTypeIcon5;

    // 天气指数
    mAqiList << ui->lblQuality0 << ui->lblQuality1 << ui->lblQuality2 << ui->lblQuality3 << ui->lblQuality4 << ui->lblQuality5;

    // 风向和风力
    mFxList << ui->lblFx0 << ui->lblFx1 << ui->lblFx2 << ui->lblFx3 << ui->lblFx4 << ui->lblFx5;
    mFlList << ui->lblFl0 << ui->lblFl1 << ui->lblFl2 << ui->lblFl3 << ui->lblFl4 << ui->lblFl5;

    mTypeMap.insert("暴雪", ":/res/type/BaoXue.png");
    mTypeMap.insert("暴雨", ":/res/type/BaoYu.png");
    mTypeMap.insert("暴雨到大暴雨", ":/res/type/BaoYuDaoDaBaoYu.png");
    mTypeMap.insert("大暴雨", ":/res/type/DaBaoYu.png");
    mTypeMap.insert("大暴雨到特大暴雨", ":/res/type/DaBaoYuDaoTeDaBaoYu.png");
    mTypeMap.insert("大到暴雪", ":/res/type/DaDaoBaoXue.png");
    mTypeMap.insert("大雪", ":/res/type/DaXue.png");
    mTypeMap.insert("大雨", ":/res/type/DaYu.png");
    mTypeMap.insert("冻雨", ":/res/type/DongYu.png");
    mTypeMap.insert("多云", ":/res/type/DuoYun.png");
    mTypeMap.insert("浮沉", ":/res/type/FuChen.png");
    mTypeMap.insert("雷阵雨", ":/res/type/LeiZhenYu.png");
    mTypeMap.insert("雷阵雨伴有冰雹", ":/res/type/LeiZhenYuBanYouBingBao.png");
    mTypeMap.insert("霾", ":/res/type/Mai.png");
    mTypeMap.insert("强沙尘暴", ":/res/type/QiangShaChenBao.png");
    mTypeMap.insert("晴", ":/res/type/Qing.png");
    mTypeMap.insert("沙尘暴", ":/res/type/ShaChenBao.png");
    mTypeMap.insert("特大暴雨", ":/res/type/TeDaBaoYu.png");
    mTypeMap.insert("undefined", ":/res/type/undefined.png");
    mTypeMap.insert("雾", ":/res/type/Wu.png");
    mTypeMap.insert("小到中雪", ":/res/type/XiaoDaoZhongXue.png");
    mTypeMap.insert("小到中雨", ":/res/type/XiaoDaoZhongYu.png");
    mTypeMap.insert("小雪", ":/res/type/XiaoXue.png");
    mTypeMap.insert("小雨", ":/res/type/XiaoYu.png");
    mTypeMap.insert("雪", ":/res/type/Xue.png");
    mTypeMap.insert("扬沙", ":/res/type/YangSha.png");
    mTypeMap.insert("阴", ":/res/type/Yin.png");
    mTypeMap.insert("雨", ":/res/type/Yu.png");
    mTypeMap.insert("雨夹雪", ":/res/type/YuJiaXue.png");
    mTypeMap.insert("阵雪", ":/res/type/ZhenXue.png");
    mTypeMap.insert("阵雨", ":/res/type/ZhenYu.png");
    mTypeMap.insert("中到大雪", ":/res/type/ZhongDaoDaXue.png");
    mTypeMap.insert("中到大雨", ":/res/type/ZhongDaoDaYu.png");
    mTypeMap.insert("中雪", ":/res/type/ZhongXue.png");
    mTypeMap.insert("中雨", ":/res/type/ZhongYu.png");

    mNetAccessManager = new QNetworkAccessManager(this);
    connect(mNetAccessManager, &QNetworkAccessManager::finished,
            this, &MainWindow::onReplied);//获取到服务器数据后会发送finished

    getWeatherInfo("重庆");//用重庆的数据进行初始化显示

    // 安装事件过滤器
    // 参数指定为 this, 也就是当前窗口对象 MainWindow
    ui->leCity->installEventFilter(this);
    ui->lblHighCurve->installEventFilter(this);
    ui->lblLowCurve->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
// 获取到网络响应调用的槽函数
void MainWindow::onReplied(QNetworkReply *reply)
{
    // 响应的状态码为200, 表示请求成功
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << statusCode << endl;
    qDebug() << "请求方式: " << reply->operation() << endl;
    qDebug() << "状态码: " << statusCode << endl;
    qDebug() << "请求的url: " << reply->url() << endl;
    qDebug() << "raw header: " << reply->rawHeaderList() << endl;

    if (reply->error() != QNetworkReply::NoError || statusCode != 200)
    {
        qDebug() << reply->errorString().toLatin1().data() << endl;
        QMessageBox::warning(this, "天气", "请求数据失败", QMessageBox::Ok);
    }
    else
    {
        QByteArray byteArray = reply->readAll();
        qDebug() << "read all : " << byteArray.data();

        // 解析 JSON 数据
        parseJson(byteArray);
    }

    // 堆上内存释放
    reply->deleteLater();
}
// 获取天气数据(发送请求)
void MainWindow::getWeatherInfo(QString cityName)
{
    // 根据城市名查找城市
    QString cityCode = WeatherTool::getCityCode(cityName);
    if (cityCode.isEmpty())
    {
        QMessageBox::warning(this, "城市编码", "城市编码获取失败", QMessageBox::Ok);
        return;
    }

    //美化界面显示
    ui->leCity->clear();
    ui->leCity->setPlaceholderText(cityName);

    QUrl url("http://t.weather.itboy.net/api/weather/city/" + cityCode);
    QNetworkRequest request(url);
    mNetAccessManager->get(request);//发送请求
}
//解析天气数据
void MainWindow::parseJson(QByteArray &byteArray)
{
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(byteArray, &err);
    if (err.error != QJsonParseError::NoError)
        return;

    QJsonObject rootObj = doc.object();
    qDebug() << rootObj.value("message").toString() << endl;

    // 1. 解析日期和城市
    mToday.date = rootObj.value("date").toString();
    mToday.city = rootObj.value("cityInfo").toObject().value("city").toString();

    //2. 解析昨天
    QJsonObject dateObj = rootObj.value("data").toObject();
    QJsonObject yesterdayObj = dateObj.value("yesterday").toObject();
    mDay[0].week = yesterdayObj.value("week").toString();
    mDay[0].date = yesterdayObj.value("ymd").toString();
    mDay[0].type = yesterdayObj.value("type").toString();
    //根据空格进行分割(高温,18°)
    QString str = yesterdayObj.value("high").toString().split(" ").at(1);//18°
    mDay[0].high = str.left(str.length() - 1).toInt();//将18赋值过去

    str = yesterdayObj.value("low").toString().split(" ").at(1);
    mDay[0].low = str.left(str.length() - 1).toInt();
    //风向和风力
    mDay[0].fx = yesterdayObj.value("fx").toString();
    mDay[0].fl = yesterdayObj.value("fl").toString();
    mDay[0].aqi = yesterdayObj["aqi"].toInt(); //污染指数

    //3. 解析预报5天后的数据
    QJsonArray forecastArr = dateObj["forecast"].toArray();
    for (int i = 0; i < 5; ++i)
    {
        QJsonObject tempObj = forecastArr[i].toObject();
        mDay[i + 1].week = tempObj.value("week").toString();
        mDay[i + 1].date = tempObj.value("ymd").toString();
        mDay[i + 1].type = tempObj.value("type").toString();

        str = tempObj.value("high").toString().split(" ").at(1); //高温 14℃
        mDay[i + 1].high = str.left(str.length() - 1).toInt();

        str = tempObj.value("low").toString().split(" ").at(1);
        mDay[i + 1].low = str.left(str.length() - 1).toInt();
        //风力和风向
        mDay[i + 1].fx = tempObj.value("fx").toString();
        mDay[i + 1].fl = tempObj.value("fl").toString();
        mDay[i + 1].aqi = tempObj["aqi"].toInt(); //污染指数
    }

    //4.解析今天的数据
    mToday.ganmao = dateObj.value("ganmao").toString();
    mToday.wendu = dateObj.value("wendu").toString().toDouble();
    mToday.shidu = dateObj.value("shidu").toString();
    mToday.pm25 = dateObj.value("pm25").toDouble();
    mToday.quality = dateObj.value("quality").toString();

    // 5. forecast中的第一个数组, 也是今天的数据
    mToday.type = mDay[1].type;

    mToday.fx = mDay[1].fx;
    mToday.fl = mDay[1].fl;

    mToday.high = mDay[1].high;
    mToday.low = mDay[1].low;

    // 6. 更新 UI
    updateUI();

    // 7.手动触发曲线 Label 的 Paint 事件
    ui->lblHighCurve->update();
    ui->lblLowCurve->update();
}
//更新UI
void MainWindow::updateUI()
{
    // 1. 更新日期和城市 240813->24/08/13
    ui->lblDate->setText(QDateTime::fromString(mToday.date, "yyyyMMdd").toString("yyyy/MM/dd") + " " + mDay[1].week);
    ui->lblCity->setText(mToday.city);

    // 2. 更新今天
    ui->lblTypeIcon->setPixmap(mTypeMap[mToday.type]);
    ui->lblTemp->setText(QString::number(mToday.wendu) + "°");
    ui->lblType->setText(mToday.type);
    ui->lblLowHigh->setText(QString::number(mToday.low) + "~" + QString::number(mToday.high) + "°C");

    ui->lblGanMao->setText("感冒指数：" + mToday.ganmao);

    ui->lblWindFx->setText(mToday.fx);
    ui->lblWindFl->setText(mToday.fl);

    ui->lblPM25->setText(QString::number(mToday.pm25));

    ui->lblShiDu->setText(mToday.shidu);

    ui->lblQuality->setText(mToday.quality);

    // 3. 更新六天
    for ( int i = 0; i < 6; i++ )
    {
        // 3.1 更新星期和日期
        mWeekList[i]->setText("周" + mDay[i].week.right(1));

        //设置 昨天/今天/明天 的星期显示 - 不显示星期几，而是显示
        //“昨天”、“今天”、“明天”
        ui->lblWeek0->setText("昨天");
        ui->lblWeek1->setText("今天");
        ui->lblWeek2->setText("明天");

        QStringList ymdList = mDay[i].date.split("-");
        mDateList[i]->setText(ymdList[1] + "/" + ymdList[2]);

        // 3.2 更新天气类型
        mTypeIconList[i]->setPixmap(mTypeMap[mDay[i].type]);
        mTypeList[i]->setText(mDay[i].type);

        // 3.3 更新空气质量
        if ( mDay[i].aqi >= 0 && mDay[i].aqi <= 50 )
        {
            mAqiList[i]->setText("优");
            mAqiList[i]->setStyleSheet("background-color: rgb(121, 184, 0);");
        }
        else if ( mDay[i].aqi > 50 && mDay[i].aqi <= 100 )
        {
            mAqiList[i]->setText("良");
            mAqiList[i]->setStyleSheet("background-color: rgb(255, 187, 23);");
        }
        else if ( mDay[i].aqi > 100 && mDay[i].aqi <= 150 )
        {
            mAqiList[i]->setText("轻度");
            mAqiList[i]->setStyleSheet("background-color: rgb(255, 87, 97);");
        }
        else if ( mDay[i].aqi > 150 && mDay[i].aqi <= 200 )
        {
            mAqiList[i]->setText("中度");
            mAqiList[i]->setStyleSheet("background-color: rgb(235, 17, 27);");
        }
        else if ( mDay[i].aqi > 200 && mDay[i].aqi <= 300 )
        {
            mAqiList[i]->setText("重度");
            mAqiList[i]->setStyleSheet("background-color: rgb(170, 0, 0);");
        }
        else
        {
            mAqiList[i]->setText("严重");
            mAqiList[i]->setStyleSheet("background-color: rgb(110, 0, 0);");
        }

        // 3.4 更新风力/风向
        mFxList[i]->setText(mDay[i].fx);
        mFlList[i]->setText(mDay[i].fl);
    }
}
//绘制高温曲线
void MainWindow::paintHighCurve()
{
    QPainter painter(ui->lblHighCurve);//绘图设备在ui->lblHighCurve上
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿

    // 1. 获取 x 轴坐标
    int pointX[6] = {0};
    for ( int i = 0; i < 6; i++ )
        pointX[i] = mWeekList[i]->pos().x() + mWeekList[i]->width() / 2;

    // 2. 获取 y 轴坐标
    int tempSum = 0;
    int tempAverage = 0;

    // 2.1 计算平均值
    for ( int i = 0; i < 6; i++ )
        tempSum += mDay[i].high;

    tempAverage = tempSum / 6; // 最高温平均值

    qDebug() << "paintHighCurve" << tempAverage;

    // 2.2 计算 y 轴坐标
    int pointY[6] = {0};
    int yCenter = ui->lblHighCurve->height() / 2;
    for ( int i = 0; i < 6; i++ )//y轴-就是向上移动
        pointY[i] = yCenter - ((mDay[i].high - tempAverage) * INCREMENT);

    // 3. 开始绘制
    // 3.1 初始化画笔
    QPen pen = painter.pen();
    pen.setWidth(1); //设置画笔宽度为1
    pen.setColor(QColor(255, 170, 0)); //设置颜色

    painter.setPen(pen);
    painter.setBrush(QColor(255, 170, 0)); //设置画刷颜色

    // 3.2 画点、写文本
    for ( int i = 0; i < 6; i++ )
    {
        painter.drawEllipse(QPoint(pointX[i], pointY[i]), POINT_RADIUS, POINT_RADIUS);
        painter.drawText(QPoint(pointX[i] - TEXT_OFFSET_X, pointY[i] - TEXT_OFFSET_Y), QString::number(mDay[i].high) + "°");
    }
    //3.3 绘制曲线
    for ( int i = 0; i < 5; i++ )
    {
        if ( i == 0 )
        {
            pen.setStyle(Qt::DotLine); //虚线
            painter.setPen(pen);
        }
        else
        {
            pen.setStyle(Qt::SolidLine); // 实线
            painter.setPen(pen);
        }
        painter.drawLine(pointX[i], pointY[i], pointX[i + 1], pointY[i + 1]);
    }
}
//绘制低温曲线
void MainWindow::paintLowCurve()
{
    // 是创建了一个QPainter对象，并将它绑定在ui->lblHighCurve小部件上
    // 操作 Painter 在 Label 上面作画
    QPainter painter(ui->lblLowCurve);

    // 抗锯齿渲染, 意味着渲染结果将更加平滑和精细
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 1. 获取 x 坐标
    int pointX[6] = {0};
    for (int i = 0; i < 6; ++i)
        pointX[i] = mWeekList[i]->pos().x() + mWeekList[i]->width() / 2;

    // 2. 获取 y 坐标
    // 2.1 得到六个高温度的平均值
    int tempSum = 0;
    int tempAve = 0;
    for (int i = 0; i < 6; ++i)
        tempSum += mDay[i].high;
    tempAve = tempSum / 6;

    // 2.2 计算 y 轴坐标
    int pointY[6] = {0};
    int yCenter = ui->lblLowCurve->height() / 2;
    for (int i = 0; i < 6; ++i)
        pointY[i] = yCenter - (mDay[i].low - tempAve) * INCREMENT;

    // 3. 开始绘制
    // 3.1 初始化画笔相关
    QPen pen = painter.pen();
    pen.setWidth(1);
    pen.setColor(QColor(0, 255, 255));
    painter.setPen(pen);
    painter.setBrush(QColor(0, 255, 255)); // 园内部填充

    // 3.2 画点、写文本
    for (int i = 0; i < 6; ++i)
    {

        // 显示温度点
        painter.drawEllipse(QPoint(pointX[i], pointY[i]), POINT_RADIUS, POINT_RADIUS);

        // 显示温度文本
        painter.drawText(pointX[i] - TEXT_OFFSET_X, pointY[i] - TEXT_OFFSET_Y, QString::number(mDay[i].low) + "°");
    }

    // 3.3 绘制曲线
    for (int i = 0; i < 5; ++i)
    {
        if (i == 0)
        {
            pen.setStyle(Qt::DotLine); // 画虚线
            painter.setPen(pen);

        }
        else
        {
            pen.setStyle(Qt::SolidLine); // 画实线
            painter.setPen(pen);
        }
        painter.drawLine(pointX[i], pointY[i], pointX[i + 1], pointY[i + 1]);
    }
}
//弹出右键菜单
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    mExitMenu->exec(QCursor::pos());

    // 调用accept 表示，这个事件我已经处理，不需要向上传递了
    event->accept();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // qDebug() << "窗口左上角：" << this->pos() << ", 鼠标坐标点：" << event->globalPosition();
        QPoint mousePos = event->globalPosition().toPoint(); //鼠标相对于屏幕的坐标
        QPoint topLeft = geometry().topLeft(); //窗口左上角相对于屏幕的坐标
        //将鼠标相对于窗口的坐标保存
        mOffset = mousePos - topLeft;
    }
    return event->accept();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() == Qt::LeftButton)
        && (event->globalPosition().toPoint() - mOffset).manhattanLength()
        > QApplication::startDragDistance())
    {
        /*  如果当前鼠标位置与上一次保存的位置之间的曼哈顿距离
            大于应用程序定义的拖动开始的距离阈值，那么就认为拖动已经开始了*/
        move(event->globalPosition().toPoint() - mOffset); //移动到"窗口相对于屏幕的坐标"
    }
    return event->accept();
}
//搜索
void MainWindow::on_btnSearch_clicked()
{
    QString cityName = ui->leCity->text();
    getWeatherInfo(cityName);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->leCity && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Enter//小键盘的Enter
            || keyEvent->key() == Qt::Key_Return)//大键盘(字母)的Enter
            on_btnSearch_clicked();
    }
    else if ( watched == ui->lblHighCurve && event->type() == QEvent::Paint )
        paintHighCurve();
    else if ( watched == ui->lblLowCurve && event->type() == QEvent::Paint )
        paintLowCurve();

    return QWidget::eventFilter(watched, event);
}

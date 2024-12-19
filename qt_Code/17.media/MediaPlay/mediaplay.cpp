#include "mediaplay.h"
#include "ui_mediaplay.h"
#include <QMediaPlaylist>
#include <QDir>
#include <QFileDialog>

MediaPlay::MediaPlay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MediaPlay)
{
    ui->setupUi(this);

    setFixedSize(1000, 700);
    mPlayer = new QMediaPlayer(this); //播放器
    mPlayList = new QMediaPlaylist(this); //播放器列表

    mPlayList->setPlaybackMode(QMediaPlaylist::Loop); //设置为循环播放模式
    mPlayer->setPlaylist(mPlayList);

    ///设置初始化声音大小
    mPlayer->setVolume(50);
    ui->slider_Volume->setMinimum(0);
    ui->slider_Volume->setMaximum(100);
    ui->slider_Volume->setValue(mPlayer->volume());

    connect (mPlayer, &QMediaPlayer::stateChanged, this, &MediaPlay::onStateChanged);
    connect (mPlayer, &QMediaPlayer::positionChanged, this, &MediaPlay::onPositionChanged);
    connect (mPlayer, &QMediaPlayer::durationChanged, this, &MediaPlay::onDurationChanged) ;
    connect (mPlayList, &QMediaPlaylist::currentIndexChanged, this, &MediaPlay::onPlaylistChanged) ;
}

MediaPlay::~MediaPlay()
{
    delete ui;
}
//更新界面上的 播放 暂停 停止按钮的使能状态。
void MediaPlay::onStateChanged(QMediaPlayer::State state)
{
    if (mPlayList->isEmpty()) return;
    //播放器状态变化，更新按钮状态
    if (state == QMediaPlayer::PlayingState)
        ui->pushButton_play->setIcon(QIcon(":/images/play.png"));
    else
        ui->pushButton_play->setIcon(QIcon(":/images/pause.png"));
}
//更新界面上显示当前媒体文件名
void MediaPlay::onPlaylistChanged(int position)
{
    //播放列表变化,更新当前播放文件名显示
    ui->listWidget->setCurrentRow(position);

    QListWidgetItem *item = ui->listWidget->currentItem();
    if (item)
        ui->label_SongName->setText ("正在播放:" + item->text()) ;
}
//更新界面上文件时间长度的显示
void MediaPlay::onDurationChanged(qint64 duration)
{
    //文件时长变化，更新进度显示
    ui->sliderPosition->setMaximum (duration) ;

    int secs = duration / 1000; //秒
    int mins = secs / 60; //分钟
    secs = secs % 60; //余数秒

    //歌曲总长度
    mDurationTime = QString("%1:%2").arg(QString::number(mins), 2, '0').arg(QString::number(secs), 2, '0');
    ui->label_curPlayTime->setText (mPositionTime + "/" + mDurationTime);//当前时长/歌曲总长度
}
//更新界面上的播放进度显示
void MediaPlay::onPositionChanged(qint64 position)
{
    //当前文件播放位置变化，更新进度显示.
    if (ui->sliderPosition->isSliderDown()) //正处于 手动调整状态，不处理
        return;

    ui->sliderPosition->setSliderPosition (position) ;
    int secs = position / 1000; //秒
    int mins = secs / 60; //分钟
    secs = secs % 60; //余数秒

    mPositionTime = QString("%1:%2").arg(QString::number(mins), 2, '0').arg(QString::number(secs), 2, '0');
    ui->label_curPlayTime->setText (mPositionTime + " /" + mDurationTime) ;
}
//添加歌曲
void MediaPlay::on_pushButton_AddSong_clicked()
{
    //添加文件
    QString curPath = QDir::homePath();
    QString dlgTitle = "选择音频文件";
    QString filter = "音频文件(* .mp3 *.wav * .wma) ;;mp3文件(* .mp3);;wav文件(* .wav); ;wma文件(*. .wma);;所有文件(*.*)";

    QStringList fileList = QFileDialog::getOpenFileNames (this, dlgTitle, curPath, filter);
    if (fileList. count() < 1)
        return;

    for (int i = 0; i < fileList.count(); ++i)
    {
        QString aFile = fileList.at(i);
        mPlayList->addMedia(QUrl::fromLocalFile(aFile));

        QFileInfo fileInfo(aFile);
        ui->listWidget->addItem(fileInfo.fileName()) ; //添加到界面文件列表
    }

    if (mPlayer->state() != QMediaPlayer::PlayingState)
        mPlayList->setCurrentIndex(0) ;

}
//移除歌曲
void MediaPlay::on_pushButton_removeSong_clicked()
{
    //移除文件
    int pos = ui->listWidget->currentRow() ;
    QListWidgetItem *item = ui->listWidget->takeItem(pos) ;
    delete item; //从listwidget里删除

    mPlayList->removeMedia(pos); //从播放列表里删除
}
//清除
void MediaPlay::on_pushButton_CleanSong_clicked()
{
    ///清空歌曲
    mPlayList->clear() ;
    ui->listWidget->clear() ;
    mPlayer->stop() ;
}
//双击时切换播放文件
void MediaPlay::on_listWidget_doubleClicked(const QModelIndex &index)
{
    int rowNo = index.row() ;
    mPlayList->setCurrentIndex(rowNo) ;//播放指定位置歌曲
    mPlayer->play() ;
}
//播放
void MediaPlay::on_pushButton_play_clicked()
{
    if (mPlayer->state() == QMediaPlayer::StoppedState
        || mPlayer->state() == QMediaPlayer::PausedState)
    {
        if (mPlayList->currentIndex() < 0)
            mPlayList->setCurrentIndex(0);
        mPlayer->play();
    }
    else
        mPlayer->pause();
}
//设置音量
void MediaPlay::on_slider_Volume_valueChanged(int value)
{
    mPlayer->setVolume(value) ;
}
//文件进度调控
void MediaPlay::on_sliderPosition_valueChanged(int value)
{
    mPlayer->setPosition(value);
}
//静音控制
void MediaPlay::on_pushButton_volumn_clicked()
{
    bool mute = mPlayer->isMuted() ;
    mPlayer->setMuted(!mute) ;
    if (mute)
        ui->pushButton_volumn->setIcon (QIcon(":/images/voice.png")) ;
    else
        ui->pushButton_volumn->setIcon (QIcon(":/images/mute.png"));
}
//前移
void MediaPlay::on_pushButton_clicked()
{
    mPlayList->previous();
    mPlayer->play();
}
//后移动
void MediaPlay::on_btnNext_clicked()
{
    mPlayList->next();
    mPlayer->play();
}

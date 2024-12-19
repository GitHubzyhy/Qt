#ifndef MEDIAPLAY_H
#define MEDIAPLAY_H

#include <QWidget>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MediaPlay;
}
QT_END_NAMESPACE

class MediaPlay : public QWidget
{
    Q_OBJECT

public:
    MediaPlay(QWidget *parent = nullptr);
    ~MediaPlay();

private slots:
    ///自定义槽函数
    void onStateChanged (QMediaPlayer::State state);//更新界面上的 播放 暂停 停止按钮的使能状态。
    void onPlaylistChanged (int position) ;//更新界面上显示当前媒体文件名
    void onDurationChanged (qint64 duration) ;//更新界面上文件时间长度的显示
    void onPositionChanged(qint64 position) ;//更新界面上的播放进度显示

    void on_pushButton_AddSong_clicked();//添加歌曲
    void on_pushButton_removeSong_clicked();//移除歌曲
    void on_pushButton_CleanSong_clicked();//清除
    void on_listWidget_doubleClicked(const QModelIndex &index);//双击切换歌曲
    void on_pushButton_play_clicked();//播放
    void on_slider_Volume_valueChanged(int value);//设置音量
    void on_sliderPosition_valueChanged(int value);//文件进度调控
    void on_pushButton_volumn_clicked();//静音

    void on_btnNext_clicked();

    void on_pushButton_clicked();

private:
    Ui::MediaPlay *ui;

    QMediaPlayer *mPlayer = nullptr; //播放器
    QMediaPlaylist *mPlayList = nullptr; //播放器列表

    QString mDurationTime = "00:00"; //总长度
    QString mPositionTime = "00:00";//当前播放到的位置
};
#endif // MEDIAPLAY_H

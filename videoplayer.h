#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <qmediaplayer.h>
#include <QMediaPlaylist>

#include <QtGui/QMovie>
#include <QtWidgets/QWidget>

class QAbstractButton;
class QSlider;
class QLabel;

class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();

public slots:
    void openFile();
    void play();

private slots:
    void mediaStateChanged(QMediaPlayer::State state);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void setPosition(int position);
    void handleError();
    void ChangePlaylist();

private:
    QMediaPlaylist lista;
    QMediaPlayer mediaPlayer;
    QAbstractButton *playButton;
    QSlider *positionSlider;
    QLabel *errorLabel;
#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <qmediaplayer.h>
#include <QMediaPlaylist>

#include <QtGui/QMovie>
#include <QtWidgets/QWidget>

class QAbstractButton;
class QSlider;
class QLabel;

class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();

public slots:
    void openFile();
    void play();

private slots:
    void mediaStateChanged(QMediaPlayer::State state);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void setPosition(int position);
    void handleError();
    void ChangePlaylist();

private:
    QMediaPlaylist lista;
    QMediaPlayer mediaPlayer;
    QAbstractButton *playButton;
    QSlider *positionSlider;
    QLabel *errorLabel;
};

#endif

};

#endif

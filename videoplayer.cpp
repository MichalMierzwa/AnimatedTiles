#include "videoplayer.h"
#include <QtWidgets>
#include <qvideowidget.h>
#include <qvideosurfaceformat.h>
#include <QDebug>

VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget(parent)
    , mediaPlayer(0, QMediaPlayer::VideoSurface)
    , playButton(0)
    , positionSlider(0)
    , errorLabel(0)
{
    QVideoWidget *videoWidget = new QVideoWidget;

    QAbstractButton *openButton = new QPushButton(tr("Open..."));
    connect(openButton, SIGNAL(clicked()), this, SLOT(openFile()));

    playButton = new QPushButton;
    playButton->setEnabled(false);
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    connect(playButton, SIGNAL(clicked()),
            this, SLOT(play()));

    positionSlider = new QSlider(Qt::Horizontal);
    positionSlider->setRange(0, 0);

    connect(positionSlider, SIGNAL(sliderMoved(int)),
            this, SLOT(setPosition(int)));

    errorLabel = new QLabel;
    errorLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setMargin(0);
    controlLayout->addWidget(openButton);
    controlLayout->addWidget(playButton);
    controlLayout->addWidget(positionSlider);

    QBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(videoWidget);
    layout->addLayout(controlLayout);
    layout->addWidget(errorLabel);

    setLayout(layout);

    mediaPlayer.setVideoOutput(videoWidget);
    connect(&mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(mediaStateChanged(QMediaPlayer::State)));
    connect(&mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(&mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    connect(&mediaPlayer, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(handleError()));

    QFileInfo info("C:\\Users\\MichaU\\Desktop\\ResonanceP1.mp4");
    QMediaPlaylist *lista = new QMediaPlaylist;
    lista->addMedia(QUrl::fromLocalFile(info.absoluteFilePath()));

    mediaPlayer.setPlaylist(lista);
    mediaPlayer.play();

    connect(lista,SIGNAL(currentIndexChanged(int)),this,SLOT(ChangePlaylist()));
}

VideoPlayer::~VideoPlayer()
{
}

void VideoPlayer::openFile()
{
    errorLabel->setText("File not opened");
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Movie"),QDir::homePath());

    if (!fileName.isEmpty()) {
        mediaPlayer.setMedia(QUrl::fromLocalFile(fileName));
        playButton->setEnabled(true);
    }
}

void VideoPlayer::play()
{
    switch(mediaPlayer.state()) {
    case QMediaPlayer::PlayingState:
        mediaPlayer.pause();
        break;
    default:
        mediaPlayer.play();
        break;
    }
}

void VideoPlayer::mediaStateChanged(QMediaPlayer::State state)
{
    switch(state) {
    case QMediaPlayer::PlayingState:
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
    default:
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    }
}

void VideoPlayer::positionChanged(qint64 position)
{
    positionSlider->setValue(position);
}

void VideoPlayer::durationChanged(qint64 duration)
{
    positionSlider->setRange(0, duration);
}

void VideoPlayer::setPosition(int position)
{
    mediaPlayer.setPosition(position);
}

void VideoPlayer::handleError()
{
    playButton->setEnabled(false);
    errorLabel->setText("Error: " + mediaPlayer.errorString());
}

void VideoPlayer::ChangePlaylist()
{
    QFileInfo info1("C:\\Users\\MichaU\\Desktop\\ResonanceP2.mp4");
    QMediaPlaylist *lista1 = new QMediaPlaylist;
    lista1->addMedia(QUrl::fromLocalFile(info1.absoluteFilePath()));
    lista1->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    mediaPlayer.setPlaylist(lista1);
    mediaPlayer.play();
}

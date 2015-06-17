#include "squareadded.h"
#include "mainwindow.h"
#include "dialog.h"
#include "videoplayer.h"
#include <QDebug>
#include <QStandardPaths>

SquareAdded::SquareAdded(const int &position, QWidget *parent) : QLabel(parent)
{ 
    this->setText(QString::number(position));
    this->setAlignment(Qt::AlignCenter);
    this->setFixedSize(100,100);
    this->setHidden(true);
    this->setAutoFillBackground(true);
    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    connect(this, SIGNAL(clicked()), this, SLOT( slotClicked()));
}

SquareAdded::~SquareAdded()
{

}

void SquareAdded::slotClicked()
{
    QColor colorClicked = this->palette().color(QWidget::backgroundRole());
    SquareClicked *SqrClicked = new SquareClicked(colorClicked);
    SqrClicked->show();

    connect(SqrClicked,SIGNAL(hideColouredButtons(QColor)),this,SIGNAL(hideColouredButtons2(QColor)));

    QPoint p  ;    
    QPropertyAnimation *animation = new QPropertyAnimation(SqrClicked, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(this->mapToGlobal(p).x(),this->mapToGlobal(p).y(),100,100));
    animation->setEndValue(QRect(this->mapToGlobal(p).x(),this->mapToGlobal(p).y(), 150,150));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();

    qDebug() << this->text();
}

void SquareAdded::mousePressEvent ( QMouseEvent * event )
{
    timer = new QTimer();
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(Tremble()));
    timer->start(1000);
    qDebug() << "Pressed";
}

void SquareAdded::mouseReleaseEvent( QMouseEvent *event)
{
    if(timer->isActive())
    {
        qDebug() << "Released - Time Remaining: " << timer->remainingTime();
        timer->stop();

        emit clicked();
    }
    else
    {
        group.setLoopCount(0);
        VideoPlayer *player = new VideoPlayer;
        player->resize(500,400);
        player->show();
    }
}

void SquareAdded::Tremble()
{
    qDebug() << "trzesie";

    QPoint p;
    int i = 1;
    int d = 10;
    mAnimation1 = new QPropertyAnimation(this, "geometry");
    mAnimation1->setDuration(d);
    mAnimation1->setStartValue(QRect(this->geometry().x(),this->geometry().y(),100,100));
    mAnimation1->setEndValue(QRect(this->geometry().x()+i,this->geometry().y(),100,100));

    mAnimation2 = new QPropertyAnimation(this, "geometry");
    mAnimation2->setDuration(d);
    mAnimation2->setStartValue(QRect(this->geometry().x()+i,this->geometry().y(),100,100));
    mAnimation2->setEndValue(QRect(this->geometry().x()+i,this->geometry().y()+i,100,100));

    mAnimation3 = new QPropertyAnimation(this, "geometry");
    mAnimation3->setDuration(d);
    mAnimation3->setStartValue(QRect(this->geometry().x()+i,this->geometry().y()+i,100,100));
    mAnimation3->setEndValue(QRect(this->geometry().x(),this->geometry().y()+i,100,100));

    mAnimation4 = new QPropertyAnimation(this, "geometry");
    mAnimation4->setDuration(d);
    mAnimation4->setStartValue(QRect(this->geometry().x(),this->geometry().y()+i,100,100));
    mAnimation4->setEndValue(QRect(this->geometry().x()-i,this->geometry().y()+i,100,100));

    mAnimation5 = new QPropertyAnimation(this, "geometry");
    mAnimation5->setDuration(d);
    mAnimation5->setStartValue(QRect(this->geometry().x()-i,this->geometry().y()+i,100,100));
    mAnimation5->setEndValue(QRect(this->geometry().x()-i,this->geometry().y(),100,100));

    mAnimation6 = new QPropertyAnimation(this, "geometry");
    mAnimation6->setDuration(d);
    mAnimation6->setStartValue(QRect(this->geometry().x()-i,this->geometry().y(),100,100));
    mAnimation6->setEndValue(QRect(this->geometry().x()-i,this->geometry().y()-i,100,100));

    mAnimation7 = new QPropertyAnimation(this, "geometry");
    mAnimation7->setDuration(d);
    mAnimation7->setStartValue(QRect(this->geometry().x()-i,this->geometry().y()-i,100,100));
    mAnimation7->setEndValue(QRect(this->geometry().x(),this->geometry().y()-i,100,100));

    mAnimation8 = new QPropertyAnimation(this, "geometry");
    mAnimation8->setDuration(d);
    mAnimation8->setStartValue(QRect(this->geometry().x(),this->geometry().y()-i,100,100));
    mAnimation8->setEndValue(QRect(this->geometry().x()+i,this->geometry().y()-i,100,100));

    mAnimation9 = new QPropertyAnimation(this, "geometry");
    mAnimation9->setDuration(1);
    mAnimation9->setStartValue(QRect(this->geometry().x(),this->geometry().y(),100,100));
    mAnimation9->setEndValue(QRect(this->geometry().x(),this->geometry().y(),100,100));

    group.addAnimation(mAnimation1);
    group.addAnimation(mAnimation2);
    group.addAnimation(mAnimation3);
    group.addAnimation(mAnimation4);
    group.addAnimation(mAnimation5);
    group.addAnimation(mAnimation6);
    group.addAnimation(mAnimation7);
    group.addAnimation(mAnimation8);
    group.addAnimation(mAnimation9);

    group.setLoopCount(-1);
    group.start();
}

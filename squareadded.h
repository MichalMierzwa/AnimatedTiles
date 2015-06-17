#ifndef SQUAREADDED_H
#define SQUAREADDED_H

#include "squareclicked.h"
#include <QWidget>
#include <QLabel>

class SquareAdded : public QLabel
{
    Q_OBJECT
public:
    explicit SquareAdded(const int & position, QWidget *parent = 0);
    ~SquareAdded();
    //QTime *time;
    QTimer *timer;


protected:
    void mouseReleaseEvent (QMouseEvent *event);
    void mousePressEvent (QMouseEvent *event);

private:
    QSequentialAnimationGroup group;

    QPropertyAnimation *mAnimation1;
    QPropertyAnimation *mAnimation2;
    QPropertyAnimation *mAnimation3;
    QPropertyAnimation *mAnimation4;
    QPropertyAnimation *mAnimation5;
    QPropertyAnimation *mAnimation6;
    QPropertyAnimation *mAnimation7;
    QPropertyAnimation *mAnimation8;
    QPropertyAnimation *mAnimation9;

signals:
    void clicked();
    void hideColouredButtons2(QColor);

public slots:
    void slotClicked();
    void Tremble();
};

#endif // SQUAREADDED_H

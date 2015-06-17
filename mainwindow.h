#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "squareclicked.h"
#include "squareadded.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
     void mouseReleaseEvent ( QMouseEvent * event );
private:
    int PickTime();
    int PickNumber();
    void pickColor();

    QColor setColor();
    QColor chosenColor;

signals:


private slots:
    void hideButtons(QColor color);

};

#endif // MAINWINDOW_H

#include "squareclicked.h"
#include "videoplayer.h"
#include <QtWidgets>

SquareClicked::SquareClicked(QColor & Color, QWidget *parent) : QWidget(parent)
{
    this->resize(150,150);

    QPalette *Pal = new QPalette;
    Pal->setColor(QPalette::Background, Qt::black);
    this->setPalette(*Pal);

    list = new QListWidget(this);
    list->addItem("cyan");
    list->addItem("magenta");
    list->addItem("red");
    list->addItem("darkRed");
    list->addItem("darkCyan");
    list->addItem("darkMagenta");
    list->addItem("green");
    list->addItem("darkGreen");
    list->addItem("yellow");
    list->addItem("blue");

    list->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

// Ustawia background listy na przezroczysty...
//    QPalette *listPal = new QPalette;
//    listPal->setColor(QPalette::Background, Qt::transparent);
//    list->setPalette(*listPal);

    QGridLayout *gr = new QGridLayout(this);
    gr->addWidget(list);
    gr->setMargin(0);
    this->setLayout(gr);

    for(int i = 0; i < 10; i++)
    {
        list->item(i)->setBackgroundColor(Color);
        list->item(i)->setTextColor(Qt::white);
    }

    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);

    //connect(this,SIGNAL(clicked()),this, SLOT(closeEnlarged()));
    connect(list, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(itemClicked(QListWidgetItem*)));


    //connect(list,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(closeEnlarged()));
}

SquareClicked::~SquareClicked()
{

}

void SquareClicked::closeEnlarged()
{
      // Działa gdy jest QListWidget wyłączony i można kliknąć na "this", czyli puste pole...
//    QPoint p;
//    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
//    animation->setDuration(1000);
//    animation->setStartValue(QRect(this->mapToGlobal(p).x(),this->mapToGlobal(p).y(),150,150));
//    animation->setEndValue(QRect(this->mapToGlobal(p).x(),this->mapToGlobal(p).y(), 100,100));
//    animation->setEasingCurve(QEasingCurve::OutBounce);
//    animation->start();
//    QTimer::singleShot(1100,this,SLOT(close()));
}

void SquareClicked::itemClicked(QListWidgetItem *item)
{
    if (!item)
    {
        return;
    }
    else
    {
        emit hideColouredButtons(QColor(item->text()));
        this->close();
    }
}

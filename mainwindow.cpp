#include "mainwindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QtCore>
#include <QMap>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{
    // Rozmiar okna głównego
    //this->setFixedSize(1000,700);

    // Seed - rand()
    qsrand(QTime::currentTime().msec());

    // GridLayout w oknie głównym
    QGridLayout* mLayout = new QGridLayout;
    mLayout->setMargin(0);
    mLayout->setSpacing(0);

    // Zmienna pomocnicza - Numer na kafelku
    int position = 0;

    // Tworzenie kafelków
    for(int i = 0; i < 10; i++)
    {
        mLayout->setRowMinimumHeight(i,100);
        mLayout->setColumnMinimumWidth(i,100);
        for(int j = 0; j < 10; j++)
        {
            SquareAdded *label = new SquareAdded(position,this);

            //SYGNAL ODEBRANY OD SQRCLICKED GDZIE WYBIERAMY KOLOR DO UKRYCIA
            connect(label,SIGNAL(hideColouredButtons2(QColor)),this,SLOT(hideButtons(QColor)));

            // Dodanie koloru do utworzonego kafelka
            QPalette palette = label->palette();
            palette.setColor(label->backgroundRole(), setColor());
            label->setPalette(palette);
            label->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

            // Dodanie kafelków do layoutu
            mLayout->addWidget(label,i,j);
            position++;

            // Pokazanie kafelka po czasie
            QTimer::singleShot(PickTime(),label,SLOT(show()));
        }
    }
//Ustawienie aktywnego layout'u
    QWidget *mainWidget = new QWidget(this);
    mainWidget->setLayout(mLayout);

    QScrollArea *area = new QScrollArea(this);
    area->setWidget(mainWidget);
    setCentralWidget(area);

//JSON wybieranie kolorow z pliku
//    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Files"));
//    QString val;
//    QFile file;
//    file.setFileName(fileName);
//    file.open(QIODevice::ReadOnly | QIODevice::Text);
//    if(file.isOpen())
//    {
//        val = file.readAll();
//        bool isJSONopened = true;
//    }

//    file.close();
//    qWarning() << val;

//    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
//    QJsonObject colorObj = doc.object();
//    QJsonValue colorVal = colorObj.value(QString("Colors"));
//    QJsonObject colorItem = colorVal.toObject();
//    QJsonArray colorArray = colorItem["colors"].toArray();
//    qDebug() << colorArray;
//  ----------------------------------------------------------------
}

void MainWindow::pickColor()
{

}

QColor MainWindow::setColor()
{
    QColor colours[10] = {QColor("cyan"), QColor("magenta"), QColor("red"),
                          QColor("darkRed"), QColor("darkCyan"), QColor("darkMagenta"),
                          QColor("green"), QColor("darkGreen"), QColor("yellow"),
                          QColor("blue")};

    int colorrnd = PickNumber();

    // Warunki by zapamiętało ile kolorow zostalo wykorzystanych
    static QMap<int, int> colourTable;
    if(!colourTable.contains(colorrnd))
    {
        colourTable.insert(colorrnd, 1);
    }
    else
    {
        Loop: if(colourTable.value(colorrnd) == 10)
        {
            colorrnd = PickNumber();
            goto Loop;
        }
        else
        {
        int temp = colourTable.value(colorrnd);
        temp += 1;
        colourTable.insert(colorrnd,temp);
        }
    }
    return colours[colorrnd];
}

int MainWindow::PickTime()
{
int low = 500;
int high = 5000;
int Time = qrand() % ((high + 1) - low) + low;
return Time;
}

int MainWindow::PickNumber()
{
    int colorrnd = rand() %10;
    return colorrnd;
}

MainWindow::~MainWindow()
{

}

void MainWindow::hideButtons(QColor color)
{
    static bool ColorChosen = false;
    QList<QLabel*> labelList = this->findChildren<QLabel *> ();
    QList<QLabel*> labelListVisible;
    if(ColorChosen == false)
    {
        for(int i = 0; i < 100; i++)
        {
            if(labelList.at(i)->palette().color(backgroundRole()) != color)
            {
                labelList.at(i)->hide();   
            }            
        }
        ColorChosen = true;

    }
    else
    {

        for(int i = 0; i < 100; i++)
        {
            if(labelList.at(i)->palette().color(backgroundRole()) == color)
            {
                labelList.at(i)->show();
            }
            else
            {
                labelList.at(i)->hide();
            }
        }
    }

    //Tworzymy liste widocznych Label jednego koloru
    foreach(QLabel* label, labelList)
    {
        if(label->isVisible())
        {
            labelListVisible.removeAll(label);
            labelListVisible.append(label);
        }
    }
    for(int i = 0; i < 10; ++i)
    {
        QPoint p ;
        QPropertyAnimation *animation = new QPropertyAnimation(labelListVisible.at(i), "geometry");
        animation->setDuration(1000);

        animation->setStartValue(QRect(labelListVisible.at(i)->mapToGlobal(p).x(),
                                       labelListVisible.at(i)->mapToGlobal(p).y(),100,100));
        animation->setEndValue(QRect(100*i,0,100,100));
        animation->start();
    }
}

void MainWindow::mouseReleaseEvent ( QMouseEvent * event )
{
    QList<QLabel*> labelList = this->findChildren<QLabel *> ();
    for(int i = 0; i < 100; i++)
    {
        labelList.at(i)->show();
    }
}


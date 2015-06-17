#ifndef SQUARECLICKED_H
#define SQUARECLICKED_H

#include <QtWidgets>
#include "mainwindow.h"
#include "squareadded.h"

class SquareClicked : public QWidget
{
    Q_OBJECT
public:
    explicit SquareClicked(QColor & Color, QWidget *parent = 0);
    ~SquareClicked();

protected:

private:
    QListWidget *list;

signals:
    void clicked();
    void hideColouredButtons(QColor);
    void changeLabelText(const QString &text);

private slots:
    void itemClicked(QListWidgetItem *item);

public slots:
    void closeEnlarged();
};

#endif // SQUARECLICKED_H

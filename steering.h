#ifndef STEERING_H
#define STEERING_H
#include"stable.h"
#include "um220.h"

class stPaintingWidget : public QWidget
{
    Q_OBJECT
public:
//    double angelCalc(QPointF);
protected:
    void paintEvent(QPaintEvent *event);
    int pWidth,pHeight;
private:
    //private slots:
    //    void showTime();
};


class Steering : public QWidget
{
    Q_OBJECT
public:
    Steering(QWidget *parent=0);
    stPaintingWidget *getStPainting() const;
    void setStPainting(stPaintingWidget *value);

private:
    QLabel *paintingLabel;
    QLabel *rngLabel;
    QLabel *ttgLabel;
    QLabel *brgLabel;
    QLabel *etaLabel;
    QLabel *spdLabel;
    QLabel *cseLabel;
    QGridLayout *mainLayout;

    QString rngString;
    QString ttgString;
    QString brgString;
    QString etaString;
    QString spdString;
    QString cseString;

protected:
    //    void paintEvent(QPaintEvent *event);
    stPaintingWidget *stPainting;

private slots:
    void showTime();

};
#endif

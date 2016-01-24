#ifndef _HIGHWAY_H_
#define _HIGHWAY_H_

#include "stable.h"
#include "um220.h"

class hwPaintingWidget : public QWidget
{
    Q_OBJECT
public:
    double angelCalc(QPointF);
protected:

    void paintEvent(QPaintEvent *event);
    int pWidth,pHeight;
private:

    //private slots:
    //    void showTime();

};

class Highway : public QWidget
{
    Q_OBJECT
public:
    Highway(QWidget *parent=0);

private:
    QTimer *timer;
    QLabel *brgLabel;
    QLabel *rngLabel;
    QLabel *spdLabel;
    QLabel *cseLabel;

    QString cseString;
    QString brgString;
    QString rngString;
    QString spdString;

    QGridLayout *mainLayout;
protected:
    //    void paintEvent(QPaintEvent *event);
    hwPaintingWidget *hwPainting;

private slots:
    void showTime();
};




#endif

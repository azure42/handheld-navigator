#ifndef _HIGHWAY_H_
#define _HIGHWAY_H_

#include "stable.h"
#include "um220.h"

class hwPaintingWidget : public QWidget
{
    Q_OBJECT
//public:
//    paintingWidget(QWidget *parent=0);
protected:
    void paintEvent(QPaintEvent *event);
//private:
//    QTimer *timer;
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

#ifndef _NAVDATA_H_
#define _NAVDATA_H_

#include "stable.h"



class NavData : public QWidget
{
    Q_OBJECT
public:
    NavData(QWidget *parent=0);
//    class um220 beidouData;
private:
    QLabel *timeLabel;
    QLabel *coordinateLabel;
    QLabel *SPDLabel;
    QLabel *CSELabel;
    QTimer *timer;
    QString coordinateString;
    QString SPDString;
    QString CSEString;
//    um220 *beidouData;
private slots:
    void showTime();
};
#endif

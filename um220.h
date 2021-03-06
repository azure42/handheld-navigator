#ifndef UM220_H
#define UM220_H
#include "posix_qextserialport.h"
#include <QPointF>
#include <QTimer>
#include <QString>



class um220 : public QThread
{
    Q_OBJECT
public:
    Posix_QextSerialPort *Com;
    void um220init();
    //    QTimer *rTimer;

    QString all;
    QString time;
    QString Lat;
    QString N;
    QString Lon;
    QString E;
    QString FS;
    QString NoSV;
    QString HDOP;
    QString msl;
    QString M;
    QString DiffAge;
    QString DiffStation;
    QString cs;

    QString spd;
    QString cog;
    QString date;
    QString mv;
    QString mvE;
    QString mode;
    double brgGet(QPointF a);

    double rngGet(QPointF targetCoor);
private :
    QTimer *rTimer;

    double rad(double d);
private slots:
    void readCom();
signals:
    void dataUpdate(void);
};

#endif //UM220_H

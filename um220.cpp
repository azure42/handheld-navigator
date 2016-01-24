#include "stable.h"
#include "um220.h"
# define PI 3.1415926535897932
#include<QPointF>

void um220::um220init()
{
    Com = new Posix_QextSerialPort("/dev/ttySAC2",QextSerialBase::Polling);
    Com ->open(QIODevice::ReadWrite);
    Com->setBaudRate(BAUD115200);
    Com->setDataBits(DATA_8);
    Com->setParity(PAR_NONE);
    Com->setStopBits(STOP_1);
    Com->setFlowControl(FLOW_OFF);
    Com->setTimeout(400);
    rTimer = new QTimer(this);
    rTimer->start(200);
    connect(rTimer,SIGNAL(timeout()),this,SLOT(readCom()));
}
void um220::readCom()
{
    QString temp = Com->readAll();
    if(temp[0]=='$')
    {
        all = temp;
        time = temp.mid(7,6);
        Lat =  temp.mid(18,11);
        N = temp.mid(30,1);
        Lon = temp.mid(32,12);
        E = temp.mid(45,1);
        FS = temp.mid(47,1);
        NoSV = temp.mid(49,1);
        spd = temp.mid(temp.indexOf("$GNRMC")+55,7);
        emit dataUpdate();
    }
}

double um220::brgGet(QPointF a)
{
    double temp,vx=a.x(),vy=a.y();
    if (vx>0 && vy==0)
        temp=0;
    else if (vx>0 && vy>0)
        temp=180*(atan(vy/vx));
    else if (vx>0 && vy<0)
        temp=180*(atan(vy/vx)+2*PI);
    else if (vx<0 && vy==0)
        temp=180*(PI);
    else if (vx<0 && vy>0)
        temp=180*(atan(vy/vx)+PI);
    else if (vx<0 && vy>0)
        temp=180*(atan(vy/vx)+PI);
    //else if (vx==0 && vy==0)
    //printf ("您输入的是同一个点");
    else if (vx==0 && vy>0)
        temp=180*(PI/2);
    else
        temp=180*(PI*3/2);

    return (temp-cog.toDouble());
}

/**
 * @rngGet
 *
 * @param 目标点地理坐标
 * @return 当前点与目标点的距离（海里）
 */
double um220::rngGet(QPointF targetCoor)
{
    return sqrt(pow((targetCoor.x()-Lon.toDouble()),2)-
                pow((targetCoor.y()-Lat.toDouble()),2));
}


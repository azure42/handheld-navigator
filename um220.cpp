#include "stable.h"
#include "um220.h"
# define PI 3.14159
#include<QPointF>
#include"math.h"

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
/**
 * @brief
 *
 */
void um220::readCom()
{
    QString temp = Com->readAll();
    if(temp[0]=='$')
    {
        all = temp;
        /*time = temp.mid(7,6);
        Lat =  temp.mid(18,11);
        N = temp.mid(30,1);
        Lon = temp.mid(32,12);
        cog = temp.mid(55,7);

        E = temp.mid(45,1);
        FS = temp.mid(47,1);
        NoSV = temp.mid(49,1);
        spd = temp.mid(temp.indexOf("$GNRMC")+55,7);*/
        
        time = QString("123456");
        Lat =  QString("123.4");
        N = QString("1");
        Lon = QString("78.4");
        E = QString("0");
        
        spd = QString("1");
        cog = QString("60.0123");
        //以上数据均需根据导航设备数据协议进行修改
        emit dataUpdate();
        
    
        
    }
}
/**
 * @brgGet
 *
 * @param 目标点地理坐标
 * @return 目标点与正北方向夹角-当前点与正北方向夹角
 *          =当前点与目标点的夹角
 */
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
double um220::rad(double d)
{
    return d * PI / 180.0;
}
double um220::rngGet(QPointF targetCoor)
{
    const double EARTH_RADIUS = 6378.137;
    const double lat1=Lat.toDouble(),lng1=Lon.toDouble(),
            lat2=targetCoor.y(),lng2=targetCoor.x();
    
    double radLat1 = rad(lat1);
    double radLat2 = rad(lat2);
    double a = radLat1 - radLat2;
    double b = rad(lng1) - rad(lng2);
    double s = 2 * asin(sqrt(pow(sin(a/2),2) +
                             cos(rad(lat1))*cos(rad(lat2))*pow(sin(b/2),2)));
    s = s * EARTH_RADIUS;
    return s;
}


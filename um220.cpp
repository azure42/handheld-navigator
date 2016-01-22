#include "stable.h"
#include "um220.h"

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


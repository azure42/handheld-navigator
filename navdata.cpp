#include "navdata.h"
#include "um220.h"

extern class um220 *beidouData;

NavData::NavData(QWidget *parent) :
    QWidget(parent)
{
    QObject::connect(beidouData,SIGNAL(dataUpdate()),this,SLOT(showTime()));
    //线程触发界面的刷新
//    QDateTime timeTemp = QDateTime::currentDateTime();
//    QString timeStr = timeTemp.toString("yyyy-MM-dd hh:mm:ss");
    //通过系统时钟获取当前时间

    timeLabel =new QLabel();
    timeLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QFont timeFont;
    timeFont.setPointSize(12);
    timeLabel->setFrameShape (QFrame::Box);
    timeLabel->setFont(timeFont);
    //timeLabel->setStyleSheet("border: 7px solid  #000000");

    coordinateLabel =new QLabel;
    coordinateLabel->setFrameShape (QFrame::Box);
    coordinateLabel->setAlignment( Qt::AlignHCenter|Qt::AlignVCenter);

    SPDLabel =new QLabel;
    SPDLabel->setFrameShape (QFrame::Box);
    SPDLabel->setAlignment( Qt::AlignHCenter|Qt::AlignVCenter);

    CSELabel =new QLabel;
    CSELabel->setFrameShape (QFrame::Box);
    CSELabel->setAlignment( Qt::AlignHCenter|Qt::AlignVCenter);

    QGridLayout *mainLayout = new QGridLayout(this);//主布局为网格
    mainLayout->setMargin(5);
    mainLayout->setSpacing(5);
    mainLayout->addWidget(timeLabel,0,0,1,2);
    mainLayout->addWidget(coordinateLabel,1,0,1,2);
    mainLayout->addWidget(SPDLabel,2,0);
    mainLayout->addWidget(CSELabel,2,1);
    mainLayout->setRowStretch(0,1);//各行高度比1:4:2
    mainLayout->setRowStretch(1,4);
    mainLayout->setRowStretch(2,2);
}

void NavData::showTime()
{
    timeLabel->setText(beidouData->time);

    CSEString = "CSE:";
    CSEString.append(beidouData->cog);
    CSEString.append("°");
    CSELabel->setText(CSEString);

    SPDString = "SPD:";
    SPDString.append(beidouData->spd);
    SPDString.append("knot");
    SPDLabel->setText(SPDString);

    coordinateString = "Longitude:";
    coordinateString.append(beidouData->Lon);
    if(beidouData->E.toInt())//东南西北判别
        coordinateString.append(QString("E\nLatitude:"));
    else
        coordinateString.append(QString("W\nLatitude:"));
    coordinateString.append(beidouData->Lat);
    if(beidouData->N.toInt())
        coordinateString.append(QString("N"));
    else
        coordinateString.append(QString("S"));
    coordinateLabel->setText(coordinateString);
}

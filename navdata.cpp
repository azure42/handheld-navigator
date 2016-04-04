#include "navdata.h"
#include "um220.h"
//test
extern class um220 *beidouData;

NavData::NavData(QWidget *parent) :
    QWidget(parent)
{
    QCursor cursor ;
    cursor = QCursor(Qt::BlankCursor);
    setCursor(cursor);
    
    QObject::connect(beidouData,SIGNAL(dataUpdate()),this,SLOT(showTime()));
    //线程触发界面的刷新
    //    QDateTime timeTemp = QDateTime::currentDateTime();
    //    QString timeStr = timeTemp.toString("yyyy-MM-dd hh:mm:ss");
    //通过系统时钟获取当前时间
    QFont font;
    font.setPointSize(35);
    
    timeLabel =new QLabel();
    
    QFont timeFont;
    timeFont.setPointSize(35);
    timeLabel->setLineWidth(3);
    timeLabel->setMidLineWidth(3);
    timeLabel->setFont(timeFont);
    
    coordinateLabel =new QLabel;
    coordinateLabel->setFont(font);
    coordinateLabel->setText("GPS unconnected!");
    SPDLabel =new QLabel;
    SPDLabel->setFont(font);
    CSELabel =new QLabel;
    CSELabel->setFont(font);
    
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

#include "steering.h"
#include "um220.h"
extern class um220 *beidouData;
extern QLinkedList <QPointF> pointList;

Steering::Steering(QWidget *parent) :
    QWidget(parent)
{
    QTimer *timer = new QTimer(this);
    timer->start(200);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    QObject::connect(beidouData,SIGNAL(dataUpdate()),this,SLOT(showTime()));

    QFont font;
    font.setPointSize(45);

    rngLabel =new QLabel(tr("RNG"));
    rngLabel->setFont(font);
    rngLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    rngLabel->setFrameShape (QFrame::Box);

    cseLabel =new QLabel(tr("CSE"));
    cseLabel->setFont(font);
    cseLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    cseLabel->setFrameShape (QFrame::Box);

    spdLabel =new QLabel(tr("SPD"));
    spdLabel->setFont(font);
    spdLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    spdLabel->setFrameShape (QFrame::Box);

    ttgLabel =new QLabel(tr("TTG"));
    ttgLabel->setFont(font);
    ttgLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ttgLabel->setFrameShape (QFrame::Box);

    brgLabel =new QLabel(tr("BRG"));
    brgLabel->setFont(font);
    brgLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    brgLabel->setFrameShape (QFrame::Box);

    etaLabel =new QLabel(tr("ETA"));
    etaLabel->setFont(font);
    etaLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    etaLabel->setFrameShape (QFrame::Box);

    paintingLabel =new QLabel(tr("PAINTING"));
    paintingLabel->setFont(font);
    paintingLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    paintingLabel->setFrameShape (QFrame::Box);

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(paintingLabel,0,0,1,2);
    mainLayout->addWidget(spdLabel,1,0);
    mainLayout->addWidget(rngLabel,2,0);
    mainLayout->addWidget(ttgLabel,3,0);
    mainLayout->addWidget(cseLabel,1,1);
    mainLayout->addWidget(brgLabel,2,1);
    mainLayout->addWidget(etaLabel,3,1);


    mainLayout->setRowStretch(0,3);
    mainLayout->setRowStretch(1,1);
    mainLayout->setRowStretch(2,1);
    mainLayout->setRowStretch(3,1);
    //    mainLayout->setColumnStretch(0,1);
    //    mainLayout->setColumnStretch(1,3);
    //mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    showTime();
}

void Steering::showTime()
{
    rngString = "RNG:";
    if(pointList.isEmpty() == false)
        rngString.append(QString::number(
                             beidouData->rngGet(pointList.first())));
    else rngString.append("NO POINT");
    rngLabel->setText(rngString);

    cseString = "CSE:";
    cseString.append(beidouData->cog);
    cseString.append("°");
    cseLabel->setText(cseString);

    spdString = "SPD:";
    spdString.append(beidouData->spd);
    spdString.append("kt");
    spdLabel->setText(spdString);


    ttgString = "TTG:";
    if(pointList.isEmpty() == false)
    {
        ttgString.append(QString::number(beidouData->rngGet(pointList.first())
                                         /beidouData->spd.toDouble()));
        ttgString.append("h");
    }
    else ttgString.append("NO POINT");
    ttgLabel->setText(ttgString);


    brgString = "BRG:";
    if(pointList.isEmpty() == false)
    {
        brgString.append(QString::number
                         (beidouData->brgGet(pointList.first())));
        brgString.append("h");
    }
    else brgString.append("NO POINT");
    brgLabel->setText(brgString);

    ttgString = "ETA:";
    if(pointList.isEmpty() == false)
    {
        QTime timeTemp;
        timeTemp.addSecs(beidouData->rngGet(pointList.first())
                         /beidouData->spd.toDouble()*3600);
        ttgString.append(timeTemp.toString("hh:mm:ss"));
        ttgString.append("h");
    }
    else ttgString.append("NO POINT");
    ttgLabel->setText(ttgString);

}

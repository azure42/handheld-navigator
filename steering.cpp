#include "steering.h"
#include "um220.h"
extern class um220 *beidouData;
extern QLinkedList <QPointF> pointList;

Steering::Steering(QWidget *parent) :
    QWidget(parent)
{
    QCursor cursor ;
    cursor = QCursor(Qt::BlankCursor);
    setCursor(cursor);

    QTimer *timer = new QTimer(this);
    timer->start(200);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    QObject::connect(beidouData,SIGNAL(dataUpdate()),this,SLOT(showTime()));

    QFont font;
    font.setPointSize(45);
    rngLabel =new QLabel(tr("RNG"));
    rngLabel->setFont(font);
    cseLabel =new QLabel(tr("CSE"));
    cseLabel->setFont(font);
    spdLabel =new QLabel(tr("SPD"));
    spdLabel->setFont(font);
    ttgLabel =new QLabel(tr("TTG"));
    ttgLabel->setFont(font);
    brgLabel =new QLabel(tr("BRG"));
    brgLabel->setFont(font);
    etaLabel =new QLabel(tr("ETA"));
    etaLabel->setFont(font);

    stPainting =new stPaintingWidget;
    stPainting->show();

    mainLayout = new QGridLayout(this);

    mainLayout->addWidget(spdLabel,1,0);
    mainLayout->addWidget(rngLabel,2,0);
    mainLayout->addWidget(ttgLabel,3,0);
    mainLayout->addWidget(cseLabel,1,1);
    mainLayout->addWidget(brgLabel,2,1);
    mainLayout->addWidget(etaLabel,3,1);
    mainLayout->addWidget(stPainting,0,0,1,2);

    mainLayout->setRowStretch(0,3);
    mainLayout->setRowStretch(1,1);
    mainLayout->setRowStretch(2,1);
    mainLayout->setRowStretch(3,1);
}

void stPaintingWidget::paintEvent(QPaintEvent *event)
{
    //手动计算paintingWidget的尺寸
    pWidth=QApplication::desktop()->width()-4*10;
    pHeight=(QApplication::desktop()->height()-7*10)/2;

    //代表船当前位置的箭头
    static const QPoint arrow[3] =
    {
        QPoint(pWidth/30, 0),
        QPoint(-pWidth/30, 0),
        QPoint(0, -pHeight/10)
    };
    setAutoFillBackground(true);
    QPalette palette;
    //    palette.setColor(QPalette::Background, Qt::white);
    setPalette(palette);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //绘制边框
    QPen pen;
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawRect(QRectF(QPointF(pWidth/10.0,pHeight/9.5),
                            QPointF(pWidth/10*9.0,pHeight/10*9.5)));

    const double kedu = pWidth/9.6;//每个刻度的像素长度（每个刻度15°）
    //    const int cog0 = beidouData->cog.toDouble()/15*15;
    const int cog0 = beidouData->cog.toDouble()/15*15;
    //    const double pianyi0 = pWidth/2-kedu*15/cog0;//恰比course小的刻度线坐标
//    const double pianyi0 = pWidth/2-kedu*15/(cog0/beidouData->cog.toDouble());//恰比course小的刻度线坐标
    const double pianyi0 = pWidth/2-kedu/15*beidouData->cog.toDouble();//恰比course小的刻度线坐标


    QFont font;
    font.setPixelSize(55);
    //绘制左半边刻度
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setFont(font);
    int i=0;
    for(double tmp=pianyi0; tmp>pWidth/10.0; tmp-=kedu,i++)
    {
        if(tmp!=pWidth/2)
        {
        painter.drawLine(tmp,pHeight/10*9.5,tmp,pHeight*0.95-pHeight/10);
        if((cog0-i*15)>0)
            painter.drawText(QPoint(tmp,pHeight/10*8),QString::number(cog0-i*15));
        else
            painter.drawText(QPoint(tmp,pHeight/10*8),QString::number(360+cog0-i*15));
        }
    }
    //绘制右半边刻度
    for(double tmp=pianyi0,i=0; tmp<pWidth/10.0*9; tmp+=kedu,i--)
    {
        painter.drawLine(tmp,pHeight/10*9.5,tmp,pHeight*0.95-pHeight/10);
        //        if((cog0-i*15)>0)
        painter.drawText(QPoint(tmp,pHeight/10*8),QString::number(cog0-i*15));
        //        else
        //            painter.drawText(QPoint(tmp,pHeight/10*8),QString::number(360+cog0-i*15));
    }

    font.setPixelSize(35);
    painter.setFont(font);

    painter.drawText(QPoint(pWidth/10.0,pHeight/2),QString("W"));
    painter.drawText(QPoint(pWidth/10.0*8.5,pHeight/2),QString("E"));

    //绘制代表船只位置的中心箭头
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::darkRed);
    painter.translate(pWidth/2,pHeight/10*10.5);
    painter.drawConvexPolygon(arrow, 3);
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

    etaString = "ETA:";
    if(pointList.isEmpty() == false)
    {
        QTime timeTemp;
        timeTemp.addSecs(beidouData->rngGet(pointList.first())
                         /beidouData->spd.toDouble()*3600);
        etaString.append(timeTemp.toString("hh:mm:ss"));
        etaString.append("h");
    }
    else ttgString.append("NO POINT");
    etaLabel->setText(etaString);


    update();
    stPainting->update();
}



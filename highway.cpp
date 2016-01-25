#include "highway.h"
#include"math.h"
#include"key.h"
extern class um220 *beidouData;
extern QLinkedList <QPointF> pointList;
int i=1;
Highway::Highway(QWidget *parent) :
    QWidget(parent)
{
    QCursor cursor ;
    cursor = QCursor(Qt::BlankCursor);
    setCursor(cursor);

    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start(200);

    QFont font;
    font.setPointSize(45);

    brgLabel =new QLabel(tr("BRG"));
    brgLabel->setFont(font);
    brgLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    brgLabel->setFrameShape (QFrame::Box);

    cseLabel =new QLabel(tr("CSE"));
    cseLabel->setFont(font);

    cseLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    cseLabel->setFrameShape (QFrame::Box);

    rngLabel =new QLabel(tr("RNG"));
    rngLabel->setFont(font);
    rngLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    rngLabel->setFrameShape (QFrame::Box);

    spdLabel =new QLabel(tr("SPD"));
    spdLabel->setFont(font);
    spdLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    spdLabel->setFrameShape (QFrame::Box);


    hwPainting = new hwPaintingWidget;
    hwPainting->show();


    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(brgLabel,0,0);
    mainLayout->addWidget(cseLabel,1,0);
    mainLayout->addWidget(spdLabel,2,0);
    mainLayout->addWidget(rngLabel,3,0);
    mainLayout->addWidget(hwPainting,0,1,4,4);

    //mainLayout->setSizeConstraint(QLayout::SetFixedSize);
}



void hwPaintingWidget::paintEvent(QPaintEvent *event)
{
    static const QPoint arrow[3] =
    {
        QPoint(20, 64),
        QPoint(-20, 64),
        QPoint(0, -30)
    };
    static const QPoint arrow2[3] =
    {
        QPoint(20, 30),
        QPoint(-20, 30),
        QPoint(0, -4)
    };
    pWidth=(QApplication::desktop()->width()-5*10)*4/5;
    pHeight=QApplication::desktop()->height()-4*10;
    //手动计算paintingWidget的尺寸

    setAutoFillBackground(true);
    QPalette palette;
    //    palette.setColor(QPalette::Background, Qt::white);
    setPalette(palette);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawLine(0,pHeight*7/8,pWidth,pHeight*7/8);
    painter.drawLine(pWidth*2/9,0,0,pHeight*7/8);
    painter.drawLine(pWidth*7/9,0,pWidth,pHeight*7/8);
    painter.drawLine(pWidth/2,0,pWidth/2,pHeight*7/8);

    double brg;
    if(pointList.isEmpty() == false)
    {
        painter.drawText(QPoint(0,0),QString::number(i));
        brg = beidouData->brgGet(pointList.first()) ;
    }
    else
    {
        brg = -45;
        painter.drawText(QPoint(pWidth / 3,pHeight /8),QString("NO Point selected(-45°for example)"));
    }
    //    painter.drawLine(QPoint(pWidth / 2,pHeight /8),QPoint(pWidth,pHeight));

    painter.translate(pWidth / 2, pHeight / 2);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.save();
    painter.rotate(brg);
    painter.drawConvexPolygon(arrow, 3);
    painter.restore();

    painter.translate(-1*brg/180*pWidth , 90);
    painter.setBrush(Qt::darkBlue);
    painter.drawConvexPolygon(arrow2, 3);  //填充时针的区域
}


void Highway::showTime()
{
    if(pointList.isEmpty() == false
            &&pointList.first().x()-beidouData->Lon.toDouble()<1.0
            &&pointList.first().x()-beidouData->Lon.toDouble()<1.0)
        //船在目标点方圆一海里以内，视为到达
    {
        pointList.removeFirst();
        i++;
    }
    cseString = "CSE:";
    cseString.append(beidouData->cog);
    cseString.append("°");
    cseLabel->setText(cseString);

    brgString = "BRG:";
    brgString.append(beidouData->cog);
    brgString.append("°");
    brgLabel->setText(brgString);

    rngString = "RNG:";
    if (pointList.isEmpty()==false)
        rngString.append(QString::number(beidouData->rngGet(pointList.first())));
    rngString.append(" NM");
    rngLabel->setText(rngString);

    spdString = "SPD:";
    spdString.append(beidouData->spd);
    spdString.append("knot");
    spdLabel->setText(spdString);

    update();
    hwPainting->update();
}


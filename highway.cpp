#include "highway.h"
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

    brgLabel =new QLabel(tr("BRG"));
    brgLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    brgLabel->setFrameShape (QFrame::Box);

    cseLabel =new QLabel(tr("CSE"));
    cseLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    cseLabel->setFrameShape (QFrame::Box);

    rngLabel =new QLabel(tr("RNG"));
    rngLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    rngLabel->setFrameShape (QFrame::Box);

    spdLabel =new QLabel(tr("SPD"));
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
    setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, Qt::white);
    setPalette(palette);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if(pointList.isEmpty() == false)
        painter.drawText(QPoint(0,0),QString::number(i));
}

//void paintingWidget::showTime()
//{
//    update();
//}

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
    brgLabel->setText(cseString);

    rngString = "RNG:";
    rngString.append(beidouData->cog);
    rngString.append(" NM");
    rngLabel->setText(cseString);

    spdString = "SPD:";
    spdString.append(beidouData->spd);
    spdString.append("knot");
    spdLabel->setText(spdString);

    update();
    hwPainting->update();
}


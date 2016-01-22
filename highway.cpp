#include "highway.h"
extern class um220 *beidouData;
Highway::Highway(QWidget *parent) :
    QWidget(parent)
{
    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start(1000);

    brgLabel =new QLabel(tr("BRG"));
    brgLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    brgLabel->setFrameShape (QFrame::Box);

    CSELabel =new QLabel(tr("CSE"));
    CSELabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    CSELabel->setFrameShape (QFrame::Box);

    rngLabel =new QLabel(tr("RNG"));
    rngLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    rngLabel->setFrameShape (QFrame::Box);

    SPDLabel =new QLabel(tr("SPD"));
    SPDLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    SPDLabel->setFrameShape (QFrame::Box);

    //    hwPainting->setAutoFillBackground(true);
    //    QPalette palette;
    //    palette.setColor(QPalette::Background, QColor(192,253,123));
    //    hwPainting->setPalette(palette);
    hwPainting = new hwPaintingWidget;
    hwPainting->show();

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(brgLabel,0,0);
    mainLayout->addWidget(CSELabel,1,0);
    mainLayout->addWidget(SPDLabel,2,0);
    mainLayout->addWidget(rngLabel,3,0);
    mainLayout->addWidget(hwPainting,0,1,4,4);

    //mainLayout->setSizeConstraint(QLayout::SetFixedSize);
}

//paintingWidget::paintingWidget(QWidget *parent) :
//    QWidget(parent)
//{
//    timer = new QTimer();
//    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
//    timer->start(1000);
//}

void hwPaintingWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawLine(QPoint(1000,1000),QPoint(0,0));
}

//void paintingWidget::showTime()
//{
//    update();
//}

void Highway::showTime()
{
    CSEString = "CSE:";
    CSEString.append(beidouData->cog);
    CSEString.append("°");
    CSELabel->setText(CSEString);

    brgString = "BRG:";
    brgString.append(beidouData->cog);
    brgString.append("°");
    brgLabel->setText(CSEString);

    SPDString = "SPD:";
    SPDString.append(beidouData->spd);
    SPDString.append("knot");
    SPDLabel->setText(SPDString);

    update();
    hwPainting->update();
}


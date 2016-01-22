#include "steering.h"

Steering::Steering(QWidget *parent) :
    QWidget(parent)
{
    RNGLabel =new QLabel(tr("RNG"));
    RNGLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    RNGLabel->setFrameShape (QFrame::Box);

    CSELabel =new QLabel(tr("CSE"));
    CSELabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    CSELabel->setFrameShape (QFrame::Box);

    SPDLabel =new QLabel(tr("SPD"));
    SPDLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    SPDLabel->setFrameShape (QFrame::Box);

    TTGLabel =new QLabel(tr("TTG"));
    TTGLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    TTGLabel->setFrameShape (QFrame::Box);

    BRGLabel =new QLabel(tr("BRG"));
    BRGLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    BRGLabel->setFrameShape (QFrame::Box);

    ETALabel =new QLabel(tr("ETA"));
    ETALabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ETALabel->setFrameShape (QFrame::Box);

    paintingLabel =new QLabel(tr("PAINTING"));
    paintingLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    paintingLabel->setFrameShape (QFrame::Box);

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(paintingLabel,0,0,1,2);
    mainLayout->addWidget(SPDLabel,1,0);
    mainLayout->addWidget(RNGLabel,2,0);
    mainLayout->addWidget(TTGLabel,3,0);
    mainLayout->addWidget(CSELabel,1,1);
    mainLayout->addWidget(BRGLabel,2,1);
    mainLayout->addWidget(ETALabel,3,1);


    mainLayout->setRowStretch(0,3);
    mainLayout->setRowStretch(1,1);
    mainLayout->setRowStretch(2,1);
    mainLayout->setRowStretch(3,1);
//    mainLayout->setColumnStretch(0,1);
//    mainLayout->setColumnStretch(1,3);
    //mainLayout->setSizeConstraint(QLayout::SetFixedSize);
}

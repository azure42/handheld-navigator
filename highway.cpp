#include "highway.h"
#include"QFont"
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
    font.setPointSize(30);
    
    brgLabel =new QLabel(tr("BRG"));
    brgLabel->setFont(font);
    cseLabel =new QLabel(tr("CSE"));
    cseLabel->setFont(font);
    rngLabel =new QLabel(tr("RNG"));
    rngLabel->setFont(font);
    spdLabel =new QLabel(tr("SPD"));
    spdLabel->setFont(font);
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
    
    pWidth=(QApplication::desktop()->width()-5*10)*4/5;
    pHeight=QApplication::desktop()->height()-4*10;
    //手动计算paintingWidget的尺寸
    
    static const QPoint arrow[3] =
    {
        QPoint(pWidth/40, pHeight/5),
        QPoint(-pWidth/40, pHeight/5),
        QPoint(0, -pHeight/5)
    };
    static const QPoint arrow2[3] =
    {
        QPoint(pWidth/20, 0),
        QPoint(-pWidth/20, 0),
        QPoint(0, -pHeight/10)
    };
    
    setAutoFillBackground(true);
    QPalette palette;
    //    palette.setColor(QPalette::Background, Qt::white);
    setPalette(palette);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    //绘制边界线
    painter.drawLine(0,pHeight*7/8,pWidth,pHeight*7/8);//下
    painter.drawLine(pWidth*2/9,0,0,pHeight*7/8);//左
    painter.drawLine(pWidth*7/9,0,pWidth,pHeight*7/8);//右
    painter.drawLine(pWidth/2,0,pWidth/2,pHeight*7/8);//中
    
    //绘制标尺
    for(int i=1;i<8;i++)
    {
        painter.drawLine(pWidth/8*i,pHeight*7/8,pWidth/8*i,pHeight*7/8-pHeight/20);
    }
    
    double brg;
    if(pointList.isEmpty() == false)
    {//若存在途径点，则显示下一目标编号
        QFont font;
        font.setPixelSize(35);
        painter.setFont(font);
        painter.drawText(QPoint(10,10),QString::number(i));
        brg = beidouData->brgGet(pointList.first()) ;
    }
    else
    {//否则显示演示角度
        brg = -45;
//        painter.drawText(QPoint(pWidth / 3,pHeight /8),QString("NO Point selected(-45°for example)"));
    }
    //    painter.drawLine(QPoint(pWidth / 2,pHeight /8),QPoint(pWidth,pHeight));
    
    //绘制航向标（蓝色）
    painter.translate(pWidth / 2, pHeight / 2);
    painter.save();
    painter.translate(0, pHeight / 4);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::darkCyan);
    painter.rotate(brg);
    painter.drawConvexPolygon(arrow, 3);
    
    //绘制船位指示标（红色）
    painter.restore();//以画布中央为初始位置
    painter.translate(-1*brg/180*pWidth , //横向移动
                      pHeight / 2);     //纵向移动
    painter.setBrush(Qt::darkRed);
    painter.drawConvexPolygon(arrow2, 3);
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


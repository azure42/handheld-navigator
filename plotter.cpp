#include "plotter.h"
#include "um220.h"
#include "qcursor.h"
#include "key.h"
#define BEISHU 0.1//一像素代表多少海里

extern class um220 *beidouData;
QLinkedList <QPointF> pointList;

/*****************
*
* 页面布局和文字刷新
* 以及画布scene初始化
*
*****************/
Plotter::Plotter(QWidget *parent) :
    QWidget(parent)
{
    QTimer *rTimer = new QTimer(this);
    rTimer->start(200);
    connect(rTimer,SIGNAL(timeout()),this,SLOT(showTime()));

    QObject::connect(beidouData,SIGNAL(dataUpdate()),this,SLOT(showTime()));

    plView =new PlView;
    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, plView->viewWidth, plView->viewHeight);

    plView->setScene(scene);
    plView->setRenderHint(QPainter::Antialiasing);//抗锯齿
    plView->centerOn(QPoint(0,0));
    plView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    //默认视野在中间,调至左上角否则无法实现鼠标全局坐标和view相对坐标的对应

    //窗口静态布局初始化
    {
        settingLabel =new QLabel(tr("Range:\nDEFAULT"));
        settingLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        settingLabel->setFrameShape (QFrame::Box);

        CSELabel =new QLabel(tr("CSE"));
        CSELabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        CSELabel->setFrameShape (QFrame::Box);

        SPDLabel =new QLabel(tr("SPD"));
        SPDLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        SPDLabel->setFrameShape (QFrame::Panel);

        coordinateLabel =new QLabel(tr("longitude\t\tlatitude"));
        coordinateLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        coordinateLabel->setFrameShape (QFrame::Box);
        mainLayout = new QGridLayout(this);
        mainLayout->addWidget(settingLabel,0,0);
        mainLayout->addWidget(CSELabel,1,0);
        mainLayout->addWidget(SPDLabel,2,0);
        mainLayout->addWidget(plView,0,1,3,1);
        mainLayout->addWidget(coordinateLabel,3,0,1,2);
        mainLayout->setRowStretch(0,2);
        mainLayout->setRowStretch(1,2);
        mainLayout->setRowStretch(2,2);
        mainLayout->setRowStretch(3,1);
        mainLayout->setColumnStretch(0,1);
        mainLayout->setColumnStretch(1,5);
    }

    //创建一个直径8像素的圆形item代表当前位置
    QGraphicsItem *zero = new QGraphicsEllipseItem(
        QRectF(plView->viewWidth/2.0,plView->viewHeight/2.0,8,8));
    //    plView->horizontalScrollBar()->setHidden(true);
    //    plView->verticalScrollBar()->setHidden(true);

    //    QPoint *temp = new QPoint(plView->mapToGlobal(QPoint(viewWidth/2,viewHeight/2)).x(),
    //                              plView->mapToGlobal(QPoint(viewWidth/2,viewHeight/2)).y());
    plView->cursor.setPos(plView->viewWidth/2+10*3+plView->viewWidth/5+1,plView->viewHeight/2+10*2+4);
    scene->addItem(zero);

}

void Plotter::showTime()
{
    //文字刷新
    CSEString = "CSE:";
    CSEString.append(beidouData->cog);
    CSEString.append("°");
    CSELabel->setText(CSEString);

    SPDString = "SPD:";
    SPDString.append(beidouData->spd);
    SPDString.append("knot");
    SPDLabel->setText(SPDString);

    QPointF nowCoor =plView->coorCalc(cursor().pos(),plView->viewWidth,plView->viewHeight);

    coordinatextring = "Longitude:";
    coordinatextring.append(QString::number(nowCoor.x()));
    if(beidouData->E.toInt())//东南西北后缀判别
        coordinatextring.append(QString("E\t\t\t\tlongitude:"));
    else
        coordinatextring.append(QString("W\t\t\t\tLatitude:"));
    coordinatextring.append(QString::number(nowCoor.y()));
    if(beidouData->N.toInt())
        coordinatextring.append(QString("N"));
    else
        coordinatextring.append(QString("S"));
    coordinateLabel->setText(coordinatextring);
}

/*****************
* coorCalc
* 输入：光标位置
* 输出：经纬度
*
*****************/
QPointF PlView::coorCalc(QPointF nowPos,int viewWidth,int viewHeight)
{
    QPoint temp= mapFromGlobal(nowPos.toPoint());
    return QPointF(beidouData->Lon.toInt()+(temp.x()-viewWidth/2.0)*BEISHU,
                   beidouData->Lat.toInt()+(temp.y()-viewHeight/2.0)*BEISHU
                  );
}


/*****************
*
* 自定义item，代表途径点
* 的小叉
*
*****************/
/*
XItem::XItem()
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
}

QRectF XItem::boundingRect() const
{
    qreal adjust = 0;
    return QRectF(-10 - adjust, -10 - adjust,
                  20 + adjust, 20 + adjust);
}

void XItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    painter->setBrush(Qt::black);
    painter->drawLine(-10,-10,10,10);
    painter->drawLine(-10,10,10,-10);

}
*/


/*****************
*
* View：整体嵌入布局
* 并负责管理光标操作
*
*****************/
PlView::PlView(QWidget *parent) :
    QGraphicsView(parent)
{
    QCursor cursor ;
    cursor = QCursor(Qt::CrossCursor);
    setCursor(cursor);
    viewWidth=(QApplication::desktop()->width()-5*10)*5/6.0;
    viewHeight=(QApplication::desktop()->height()-7*10)*6/7.0;
    //    cursor.setPos(QPoint(500,400));
}

/*****************
*
* key.c中接收自定义按键数据,
* 发送keyEvent,在本函数中处理
* 不用自定义事件是为了便于调试
* 和增强可移植性
*
*****************/
void PlView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {

    case Qt::Key_Equal ://缩放视野,坐标体系不变
        scale(1.2, 1.2);//按键不够用，考虑用激活右键惨淡实现
        break;
    case Qt::Key_Minus :
        scale(1 / 1.2, 1 / 1.2);
        break;

    case Qt::Key_Up ://上下左右移动光标
        if(cursor.pos().y()> PlView::pos().y() )//防止光标越界
            cursor.setPos((QPoint(cursor.pos().x(),cursor.pos().y()-8)));
        break;
    case Qt::Key_Down :
        if(cursor.pos().y() < (PlView::pos().y() + PlView::height()) )
            cursor.setPos((QPoint(cursor.pos().x(),cursor.pos().y()+8)));
        break;
    case Qt::Key_Left :
        if(cursor.pos().x() > PlView::pos().x() )
        {
            cursor.setPos((QPoint(cursor.pos().x()-8,cursor.pos().y())));
        }
        break;
    case Qt::Key_Right :
        if(cursor.pos().x() < (PlView::pos().x()+ PlView::width()))
        {
            cursor.setPos((QPoint(cursor.pos().x()+8,cursor.pos().y())));
        }
        break;


    case Qt::Key_Space :   //管理途径点,以16x16的正方形和数字表示
    {
        QGraphicsItem *pItemAt = scene()->itemAt(QPoint(//若当前光标处有item，则删除
                                     mapFromGlobal(QCursor::pos()).x()-8,
                                     mapFromGlobal(QCursor::pos()).y()-8));
        static int i=1;

        if(pItemAt== 0)   //添加
        {
            QGraphicsRectItem *rect = new QGraphicsRectItem (mapFromGlobal(QCursor::pos()).x()-8,
                    mapFromGlobal(QCursor::pos()).y()-8,
                    16,16);
            QGraphicsSimpleTextItem *text = new QGraphicsSimpleTextItem(QString::number(i++));
            text->setPos(QPoint(mapFromGlobal(QCursor::pos()).x()-8,
                                mapFromGlobal(QCursor::pos()).y()-12));

            scene()->addItem(rect);
            scene()->addItem(text);
            itemList.append(text);//存储item的指针，便于控制图形显示
            pointList.append(text->pos());//存储目标点的屏幕坐标

            // QLinkedList<QGraphicsSimpleTextItem*>::iterator iter;
            // for(iter=itemList.begin();iter!= itemList.end();iter++)
            //     qDebug()<<(*iter)->pos().x();

        }
        /*
                    XItem *item = new XItem;
                    item->setPos(mapFromGlobal(QCursor::pos()).x()-10,
                                 mapFromGlobal(QCursor::pos()).y()-10);
                    scene()->addItem(item);
        自定义item不能被itemAt识别？无法正常删除
        */
        else
        {
            //删除，鼠标itemAt-》获取指针-》通过指针控制图形-》修改itemList
            //                         ↓-》获取坐标-》修改pointList
            scene()->removeItem(pItemAt);//两次删除，分别删除数字和方框
            scene()->removeItem(scene()->itemAt(QPoint(mapFromGlobal(QCursor::pos()).x()-8,
                                                mapFromGlobal(QCursor::pos()).y()-8)));
            QLinkedList<QGraphicsSimpleTextItem*>::iterator it
                =qFind(itemList.begin(),itemList.end(),pItemAt);
            if(it!=itemList.end())
                it = itemList.erase(it);
            else itemList.removeLast();//在链表中删除选中点，此时it指向被删除点的下一个点
            i--;
            while (it != itemList.end())
            {
                //此点及以后的点标号减一
                (*it)->setText(QString::number(
                                   (*it)->text().toInt()-1));
                it++;
            }
        }
        pointList.clear();//pointList与itemList同步
        QLinkedList<QGraphicsSimpleTextItem*>::iterator it1;
        QLinkedList<QPointF>::iterator it2;
        for(it1=itemList.begin(),it2=pointList.begin(); it1!=itemList.end(); it1++,it2++)
        {
            (*it2) = coorCalc(mapToGlobal((*it1)->pos().toPoint()),viewWidth,viewHeight);
//            qDebug()<<(*it2).x();
        }

    }
    break;
    }

}



#include "plotter.h"
#include "um220.h"
#include "qcursor.h"
#include "key.h"
#define BEISHU 0.1//一像素代表多少海里
//test
extern class um220 *beidouData;
extern class readKey *readKeyThread;

/*****************
*
* 页面布局和文字刷新
* 以及画布scene初始化
*
*****************/
Plotter::Plotter(QWidget *parent) :
    QWidget(parent)
{
    //    QObject::connect(readKeyThread,SIGNAL(dirKey(int)),plView, SLOT(dirGet(int)));//方向键

    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, 4000, 3000);
    plView =new PlView;
    plView->setScene(scene);
    plView->setRenderHint(QPainter::Antialiasing);
    //    const QPoint zero = QPoint(plView->width())

    QGraphicsItem *zero = new QGraphicsEllipseItem(
                QRectF(plView->width()/2.0+150,
                plView->height()/2.0+50,
                10,10));
    scene->addItem(zero);

    //    scene->addEllipse(QRectF(plView->width()/2.0+150,
//                             plView->height()/2.0+50,
//                             10,10));//用圆形表示当前位置

    //   plView->centerOn(QPoint(plView->width()/2,plView->height()/2));
    plView->centerOn(QPoint(0,0));
    //    plView->scroll(0,0);
    {
        settingLabel =new QLabel(tr("SETTING"));
        settingLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        settingLabel->setFrameShape (QFrame::Box);

        CSELabel =new QLabel(tr("CSE"));
        CSELabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        CSELabel->setFrameShape (QFrame::Box);

        SPDLabel =new QLabel(tr("SPD"));
        SPDLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        SPDLabel->setFrameShape (QFrame::Box);

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
}

void Plotter::showTime()
{
    CSEString = "CSE:";
    CSEString.append(beidouData->cog);
    CSEString.append("°");
    CSELabel->setText(CSEString);

    SPDString = "SPD:";
    SPDString.append(beidouData->spd);
    SPDString.append("knot");
    SPDLabel->setText(SPDString);

    coordinateString = "Longitude:";
    const QPointF nowCoor =plView->coorCalc( mapFromGlobal(cursor().pos()));
    coordinateString.append(QString::number(nowCoor.x()));
    if(beidouData->E.toInt())//东南西北后缀判别
        coordinateString.append(QString("E\nLatitude:"));
    else
        coordinateString.append(QString("W\nLatitude:"));
    coordinateString.append(QString::number(nowCoor.y()));
    if(beidouData->N.toInt())
        coordinateString.append(QString("N"));
    else
        coordinateString.append(QString("S"));
    coordinateLabel->setText(coordinateString);
}

/*****************
*
* 输入：屏幕坐标
* 输出：经纬度
*
*****************/
QPointF PlView::coorCalc(QPoint nowPos)
{
    return QPointF(beidouData->Lon.toInt()+(nowPos.x()-zero->pos().x())*BEISHU,
                   beidouData->Lat.toInt()+(nowPos.y()-zero->pos().y())*BEISHU
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
    cursor.setPos(QPoint(500,400));
}

void PlView::dirGet(int num)
{
    switch (num)
    {
    case 1 ://上
        cursor.setPos((QPoint(cursor.pos().x(),cursor.pos().y()-10)));
        break;
    case 2 ://下
        cursor.setPos((QPoint(cursor.pos().x(),cursor.pos().y()+10)));
        break;
    case 3 ://左
        cursor.setPos((QPoint(cursor.pos().x()-10,cursor.pos().y())));
        break;
    case 4 ://右
        cursor.setPos((QPoint(cursor.pos().x()+10,cursor.pos().y())));
        break;
        //     case 5://确认键，添加点或删除选中点

    case Qt::Key_Equal :
        scale(1.2, 1.2);
        break;
    case Qt::Key_Minus :
        scale(1 / 1.2, 1 / 1.2);
        break;
    case Qt::Key_0 :
        rotate(30);
        break;

    }
    //    QGraphicsView::keyPressEvent(event);
}

void PlView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {

    case Qt::Key_Equal ://缩放
        scale(1.2, 1.2);
        break;
    case Qt::Key_Minus :
        scale(1 / 1.2, 1 / 1.2);
        break;

    case Qt::Key_Up ://上下左右移动光标
        if(cursor.pos().y()> PlView::pos().y() )//防止光标越界
            cursor.setPos((QPoint(cursor.pos().x(),cursor.pos().y()-10)));
        break;
    case Qt::Key_Down :
        if(cursor.pos().y() < (PlView::pos().y() + PlView::height()) )
            cursor.setPos((QPoint(cursor.pos().x(),cursor.pos().y()+10)));
        break;
    case Qt::Key_Left :
        if(cursor.pos().x() > PlView::pos().x() )
        {   cursor.setPos((QPoint(cursor.pos().x()-10,cursor.pos().y())));
            qDebug("Key_Left");
        }break;
    case Qt::Key_Right :
        if(cursor.pos().x() < (PlView::pos().x()+ PlView::width()))
        {   cursor.setPos((QPoint(cursor.pos().x()+10,cursor.pos().y())));
            qDebug("Key_Right");
        }break;


    case Qt::Key_Space ://管理途径点
    {//若当前光标处有item，则删除
        if(scene()->itemAt(QPoint(
                               mapFromGlobal(QCursor::pos()).x()-10,
                               mapFromGlobal(QCursor::pos()).y()-10)
                           )== 0)
        {scene()->addRect(
                        mapFromGlobal(QCursor::pos()).x()-10,
                        mapFromGlobal(QCursor::pos()).y()-10,
                        20,20);

        }
        //        {
        //            XItem *item = new XItem;
        //            item->setPos(mapFromGlobal(QCursor::pos()).x()-10,
        //                         mapFromGlobal(QCursor::pos()).y()-10);
        //            scene()->addItem(item);
        //        }
        //自定义item不能被itemAt识别？
        else scene()->removeItem(scene()->itemAt(QPoint(
                                                     mapFromGlobal(QCursor::pos()).x()-10,
                                                     mapFromGlobal(QCursor::pos()).y()-10)));
    }break;
    }
}

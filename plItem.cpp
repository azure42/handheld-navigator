#include "plItem.h"
#include"stable.h"
QRectF PlItem::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-10 - adjust, -10 - adjust,
                  20 + adjust, 20 + adjust);
}

void PlItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget)
{
//    if(hasFocus()) {
        painter->setPen(QPen(QColor(255,255,255,200)));
//    } else {
//        painter->setPen(QPen(QColor(100,100,100,100)));
//    }
//    painter->setBrush(brushColor);
    painter->drawRect(-10, -10, 20, 20);
}

/*
// 鼠标按下事件处理函数，设置被点击的图形项获得焦点，并改变光标外观
void PlItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setFocus();
    setCursor(Qt::PointingHandCursor);
}


// 悬停事件处理函数，设置光标外观和提示
void PlItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::PointingHandCursor);
    setToolTip("I am item");
}

// 右键菜单事件处理函数，为图形项添加一个右键菜单
void PlItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QAction *deleteAction = menu.addAction("delte point");
    QAction *selectedAction = menu.exec(event->screenPos());
    if(selectedAction == deleteAction) {
        setPos(0, 0);
    }
}
*/


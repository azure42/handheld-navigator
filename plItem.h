#ifndef PLITEM_H
#define PLITEM_H

#include <QGraphicsItem>

class PlItem : public QGraphicsItem
{
public:
    PlItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget);
    void setColor(const QColor &color) { brushColor = color; }

protected:
//    void keyPressEvent(QKeyEvent *event);
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
//    QGraphicsSceneContextMenuEvent *event;
//    QKeyEvent *event;

private:
    QColor brushColor;
public slots:
//    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
signals:
//    void moniyoujian(void);

};


#endif // PLITEM_H

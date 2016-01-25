
#ifndef _PLOTTER_H_
#define _PLOTTER_H_
#include "stable.h"



class PlView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit PlView(QWidget *parent = 0);
    QPointF coorCalc(QPointF nowPos, int viewWidth, int viewHeight);
    QCursor cursor;
    QGraphicsItem *zero;
    QLinkedList<QGraphicsSimpleTextItem*> itemList;
    int viewWidth,viewHeight;
protected:
//    void keyPressEvent(QKeyEvent *event);
    double cseCalc(QPoint nowPos, int viewWidth, int viewHeight);
signals:

public slots:
        void dirGet(int i);
};

class XItem : public QGraphicsItem
{
public:
    XItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    //    void setColor(const QColor &color) { brushColor = color; }
protected:
private:
public slots:
signals:

};


class Plotter : public QWidget
{
    Q_OBJECT
public:
    Plotter(QWidget *parent=0);

private:
    QLabel *settingLabel;
    QLabel *coordinateLabel;
    QLabel *SPDLabel;
    QLabel *CSELabel;
    PlView *plView;
    QGraphicsScene *scene;
    QString coordinatextring;
    QString SPDString;
    QString CSEString;
    QGridLayout *mainLayout;

protected:
    //  void mousePressEvent(QMouseEvent *event);

public slots:
    void showTime();

};




#endif

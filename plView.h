#ifndef PLSCENE_H
#define PLSCENE_H

#include "stable.h"

class PlView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit PlView(QWidget *parent = 0);

protected:
    QCursor cursor;
    void keyPressEvent(QKeyEvent *event);

signals:

public slots:
    void dirGet(int);
};


#endif // PLSCENE_H

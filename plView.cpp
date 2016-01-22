#include "qcursor.h"
#include "content.h"
#include "plView.h"
#include "key.h"
#include "plItem.h"


PlView::PlView(QWidget *parent) :
    QGraphicsView(parent)
{
    QCursor cursor ;
    cursor = QCursor(Qt::CrossCursor);
    setCursor(cursor);
    cursor.setPos(QPoint(400,400));

}


void PlView::dirGet(int num)
{
    switch (num)
    {
//改为QWSServer::sendKeyEvent调用系统按键，PC调试方便
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
    case Qt::Key_Equal :
        scale(1.2, 1.2);
        break;
    case Qt::Key_Minus :
        scale(1 / 1.2, 1 / 1.2);
        break;
    case Qt::Key_0 :
        rotate(30);
        break;
     case Qt::Key_Up :
        if(cursor.pos().y()> PlView::pos().y() )//防止光标越界
            cursor.setPos((QPoint(cursor.pos().x(),cursor.pos().y()-10)));
        break;
    case Qt::Key_Down :
        if(cursor.pos().y() < (PlView::pos().y() + PlView::height()) )
        cursor.setPos((QPoint(cursor.pos().x(),cursor.pos().y()+10)));
        break;
    case Qt::Key_Left :
        if(cursor.pos().x() > PlView::pos().x() )
        cursor.setPos((QPoint(cursor.pos().x()-10,cursor.pos().y())));
        break;
    case Qt::Key_Right :
        if(cursor.pos().x() > (PlView::pos().x()+ PlView::width()))
        cursor.setPos((QPoint(cursor.pos().x()+10,cursor.pos().y())));
        break;
    }
//    QGraphicsView::keyPressEvent(event);
}

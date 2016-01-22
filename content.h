#ifndef _CONTENT_H_
#define _CONTENT_H_
//添加的头文件
//#include "stable.h"
#include "navdata.h"
#include "plotter.h"
#include "highway.h"
#include "steering.h"
#include "key.h"

class Content : public QFrame
{
    Q_OBJECT
public:
    Content(QWidget *parent=0);
    QStackedWidget *stack;

    NavData  *navdata;
    Plotter *plotter;
    Highway *highway;
    Steering *steering;
//    readKey *readKeyThread;
};
#endif

#include "content.h"
Content::Content(QWidget *parent):
    QFrame(parent)
{
    stack =new QStackedWidget();
    stack->setFrameStyle(QFrame::Panel|QFrame::Raised);//视觉风格
    navdata =new NavData();
    plotter =new Plotter();//栈内的三个页面
    highway =new Highway();
    steering = new Steering();
    //    readKeyThread = new readKey;
    stack->addWidget(navdata);//添加三个页面对象到栈
    stack->addWidget(plotter);
    stack->addWidget(highway);
    stack->addWidget(steering);

    QVBoxLayout *RightLayout =new QVBoxLayout(this);//右侧布局为一个整体，由页面和按钮构成，为竖直布局
    //    RightLayout->setMargin(1);
    //    RightLayout->setSpacing(1);
    RightLayout->addWidget(stack);
}

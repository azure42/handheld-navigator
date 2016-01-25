#include "content.h"
#include "um220.h"
#include "key.h"

um220 *beidouData = new um220;
readKey *readKeyThread = new readKey;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font("CONSOLAS",18);
    a.setFont(font);
    QSplitter *splitterMain =new QSplitter(Qt::Horizontal,0);//主框架
    splitterMain->setOpaqueResize(true);

    QListWidget *list =new QListWidget(splitterMain);//添加左侧列表
    list->insertItem(0,QObject::tr("Nav Data Display"));
    list->insertItem(1,QObject::tr("Plotter Display"));
    list->insertItem(2,QObject::tr("Highway Display"));
    list->insertItem(3,QObject::tr("Steering Display"));

    Content *content =new Content(splitterMain);
    readKeyThread->start();

    content->stack->setCurrentIndex(0);//临时切换到plotter Display

    QObject::connect(readKeyThread,SIGNAL(disSwitch(int)),
                     content->stack, SLOT(setCurrentIndex(int)));//切换界面
    content->stack->setCurrentIndex(2);
    list->hide();//隐藏list
    beidouData->um220init();
//splitterMain->show();
    splitterMain->showFullScreen();
    return a.exec();
}

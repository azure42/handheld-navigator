#include "content.h"
#include "um220.h"
#include "key.h"

um220 *beidouData = new um220;
readKey *readKeyThread = new readKey;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //设置字符编码为UTF-8，解决特殊符号乱码的问题
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    //主框架
    QSplitter *splitterMain =new QSplitter(Qt::Horizontal,0);
    splitterMain->setOpaqueResize(true);
    //添加左侧列表
    QListWidget *list =new QListWidget(splitterMain);
    list->insertItem(0,QObject::tr("Nav Data Display"));
    list->insertItem(1,QObject::tr("Plotter Display"));
    list->insertItem(2,QObject::tr("Highway Display"));
    list->insertItem(3,QObject::tr("Steering Display"));
    Content *content =new Content(splitterMain);
    //页面切换功能
    readKeyThread->start();
    QObject::connect(readKeyThread,SIGNAL(disSwitch(int)),
                     content->stack, SLOT(setCurrentIndex(int)));
    content->stack->setCurrentIndex(3);//0~3:NPHS
    list->hide();//隐藏左侧列表
    
    beidouData->um220init();//北斗模块初始化
    //从资源文件中载入style sheet
    QFile file(":/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);
    //展示窗口
    splitterMain->showFullScreen();
    return a.exec();
}

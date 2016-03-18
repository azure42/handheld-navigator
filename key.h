#ifndef KEY_H
#define KEY_H

#include "stable.h"
#include <QThread>

class readKey : public QThread
{
    Q_OBJECT
public:
    explicit readKey(QObject *parent = 0);
    //    void keyInit();
    volatile int indexNum;
protected:
    void keyPressEvent(QKeyEvent *event);
private:
    volatile bool initFlag;
    volatile int fd;

    void run();
signals:
    void disSwitch(int);
    void dirKey(int);
public slots:

};

#endif // KEY_H

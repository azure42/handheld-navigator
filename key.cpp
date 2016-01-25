//#include <stdio.h>
//#include <sys/types.h>
//#include <sys/stat.h>
#include <fcntl.h>
#include <key.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include<QDebug>
#include <QWSServer>

#define KEYCOUNTS 6

readKey::readKey(QObject *parent) :
    QThread(parent)
{
    initFlag = false;
    indexNum = 1;
}


void readKey::run()
{
    int keyValue[KEYCOUNTS];
    int i;
    while(1)
    {
        if( !initFlag )
        {
            fd = open("/dev/key",0);
            initFlag = ~initFlag;
        }

        read(fd,keyValue, sizeof(keyValue));

        for(i=0; i<KEYCOUNTS; i++)
        {
            if(keyValue[i] == 1)   //1还是0代表按下来着？
            {
                switch(i)
                {
                case 0:
                {
                        emit disSwitch(indexNum);
                        indexNum = (indexNum+1)%4;

                }
                break;
                case 1:
                    emit dirKey(1);
                    break;
                case 2:
                    emit dirKey(2);
                    break;
                case 3:
                    emit dirKey(3);
                    break;
                case 4:
                    emit dirKey(4);
                    break;
                case 5://确认键
                    emit dirKey(5);
                    break;
                }
            }
        }
    }
}

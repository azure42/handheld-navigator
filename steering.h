#ifndef STEERING_H
#define STEERING_H
#include"stable.h"

class Steering : public QWidget
{
    Q_OBJECT
public:
    Steering(QWidget *parent=0);
private:
    QLabel *paintingLabel;
    QLabel *rngLabel;
    QLabel *ttgLabel;
    QLabel *brgLabel;
    QLabel *etaLabel;
    QLabel *spdLabel;
    QLabel *cseLabel;
    QGridLayout *mainLayout;

    QString rngString;
    QString ttgString;
    QString brgString;
    QString etaString;
    QString spdString;
    QString cseString;

private slots:
    void showTime();

};
#endif

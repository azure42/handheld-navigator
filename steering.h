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
    QLabel *RNGLabel;
    QLabel *TTGLabel;
    QLabel *BRGLabel;
    QLabel *ETALabel;
    QLabel *SPDLabel;
    QLabel *CSELabel;
    QGridLayout *mainLayout;


};
#endif

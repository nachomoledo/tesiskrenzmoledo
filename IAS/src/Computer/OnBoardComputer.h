#ifndef ONBOARDCOMPUTER_H
#define ONBOARDCOMPUTER_H

#include "Computer.h"

class OnBoardComputer : public Computer
{
private:
    bool m_led;
public:
    OnBoardComputer(QString name);
    bool getLed() const;
    void setLed(bool led);
};

#endif // ONBOARDCOMPUTER_H

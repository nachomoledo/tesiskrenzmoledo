#include "ScreenProperties.h"

ScreenProperties::ScreenProperties(QObject *parent)
    : QObject(parent)
{

}

int ScreenProperties::getScreenWidth(void)
{
    return 1366;
}

int ScreenProperties::getScreenHeight(void)
{
    return 768;
}

int ScreenProperties::getButtonWidth(void)
{
    return 280;
}

int ScreenProperties::getButtonHeight(void)
{
    return 50;
}

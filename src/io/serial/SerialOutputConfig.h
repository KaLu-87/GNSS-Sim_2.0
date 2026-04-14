#pragma once
#include <QString>

struct SerialOutputConfig
{
    QString portName;
    int baudRate {115200};
};
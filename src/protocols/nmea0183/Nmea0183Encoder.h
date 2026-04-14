#pragma once

#include "../../domain/SimulatorState.h"
#include <QStringList>

class Nmea0183Encoder
{
public:
    QStringList encodeAll(const SimulatorState& state) const;
};

#include "Nmea0183Encoder.h"
#include "GgaEncoder.h"

QStringList Nmea0183Encoder::encodeAll(const SimulatorState& state) const
{
    return {
        GgaEncoder::encode(state)
    };
}

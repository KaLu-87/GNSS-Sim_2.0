#include "Nmea0183Encoder.h"
#include "GgaEncoder.h"
#include "RmcEncoder.h"
#include "VtgEncoder.h"
#include "HdtEncoder.h"
#include "ZdaEncoder.h"

QStringList Nmea0183Encoder::encodeAll(const SimulatorState& state) const
{
    return {
        GgaEncoder::encode(state),
        RmcEncoder::encode(state),
        VtgEncoder::encode(state),
        HdtEncoder::encode(state),
        ZdaEncoder::encode(state)
    };
}
#pragma once

#include "../../domain/SimulatorState.h"
#include "NmeaFormatUtils.h"
#include "NmeaChecksum.h"
#include <QString>

class GgaEncoder
{
public:
    static QString encode(const SimulatorState& state)
    {
        QString latHem;
        QString lonHem;

        const QString lat = NmeaFormatUtils::formatLat(state.position.lat_deg, latHem);
        const QString lon = NmeaFormatUtils::formatLon(state.position.lon_deg, lonHem);
        const QString utc = NmeaFormatUtils::formatUtcTimeHhmmss(state.utc);

        const QString quality = NmeaFormatUtils::fixTypeToGgaQuality(state.quality.fix);
        const QString sats = QString::number(state.quality.satellitesUsed);
        const QString hdop = QString::number(state.quality.hdop, 'f', 1);
        const QString alt = QString::number(state.position.alt_m, 'f', 1);

        const QString body = QString("GPGGA,%1,%2,%3,%4,%5,%6,%7,%8,%9,M,0.0,M,,")
                .arg(utc)
                .arg(lat)
                .arg(latHem)
                .arg(lon)
                .arg(lonHem)
                .arg(quality)
                .arg(sats, 2, 10, QChar('0'))
                .arg(hdop)
                .arg(alt);

        return NmeaChecksum::addChecksum(body);
    }
};

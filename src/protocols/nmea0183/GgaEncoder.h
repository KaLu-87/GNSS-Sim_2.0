/******************************************************************************
 * @file        GgaEncoder.h
 * @brief       Encoder for NMEA 0183 GGA sentences
 *
 * @details
 * GGA contains essential GNSS fix data, including:
 *  - UTC time
 *  - latitude / longitude
 *  - fix quality
 *  - satellites used
 *  - HDOP
 *  - altitude
 *
 * @author      KaLu-87
 * @date        2026-04-15
 ******************************************************************************/

#pragma once

#include "../../domain/SimulatorState.h"
#include "NmeaFormatUtils.h"
#include "NmeaChecksum.h"
#include <QString>

/**
 * @class GgaEncoder
 * @brief Encodes GGA sentences from the current simulator state
 */
class GgaEncoder
{
public:
    /**
     * @brief Encodes a GGA sentence
     *
     * @param state Current simulator state
     * @return Complete GGA NMEA sentence including checksum and CRLF
     */
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
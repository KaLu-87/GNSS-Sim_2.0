/******************************************************************************
 * @file        Nmea0183Encoder.h
 * @brief       Aggregates supported NMEA 0183 sentence encoders
 *
 * @details
 * This class generates the configured set of NMEA 0183 sentences from the
 * current simulator state. It serves as the central protocol encoder for
 * RS232 output.
 *
 * @author      KaLu-87
 * @date        2026-04-15
 ******************************************************************************/

#pragma once

#include "../../domain/SimulatorState.h"
#include <QStringList>

/**
 * @class Nmea0183Encoder
 * @brief Aggregates NMEA sentence generation for a simulator state
 */
class Nmea0183Encoder
{
public:
    /**
     * @brief Encodes all supported NMEA 0183 sentences
     *
     * @param state Current simulator state
     * @return List of complete NMEA 0183 sentences
     */
    QStringList encodeAll(const SimulatorState& state) const;
};
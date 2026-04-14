/******************************************************************************
 * @file        SimulatorState.h
 * @brief       Domain model for the GNSS simulator state
 *
 * @details
 * This file contains the core data structures used throughout the GNSS
 * simulator. The SimulatorState acts as the single source of truth for:
 *  - current UTC timestamp
 *  - geographic position
 *  - motion state
 *  - GNSS quality information
 *
 * All protocol encoders and output adapters shall consume data from this
 * model to ensure consistent output across RS232, J1939 and NMEA 2000.
 *
 * @author      KaLu-87
 * @date        2026-04-15
 ******************************************************************************/

#pragma once

#include <chrono>

/**
 * @struct GeoPosition
 * @brief Represents a geographic position in WGS84-like coordinates
 *
 * @details
 * The position consists of:
 *  - latitude in decimal degrees
 *  - longitude in decimal degrees
 *  - altitude in meters
 */
struct GeoPosition
{
    double lat_deg {0.0};   ///< Latitude in decimal degrees
    double lon_deg {0.0};   ///< Longitude in decimal degrees
    double alt_m {0.0};     ///< Altitude above mean sea level in meters
};

/**
 * @struct MotionState
 * @brief Represents the dynamic motion state of the simulated vehicle
 *
 * @details
 * This struct separates:
 *  - speed
 *  - course over ground (movement direction)
 *  - true heading (vehicle orientation)
 *  - reversing state
 *
 * @note
 * Heading and course over ground are intentionally separated because they
 * may differ during reversing or special motion situations.
 */
struct MotionState
{
    double speed_mps {0.0};                  ///< Vehicle speed in meters per second
    double course_over_ground_deg {0.0};     ///< Direction of movement in degrees true
    double heading_deg_true {0.0};           ///< Vehicle heading in degrees true
    bool reversing {false};                  ///< True if vehicle is reversing
};

/**
 * @enum FixType
 * @brief GNSS fix quality classification
 *
 * @details
 * This enum represents the simplified GNSS quality state used by the
 * simulator and later mapped to NMEA, J1939 or NMEA 2000 representations.
 */
enum class FixType
{
    NoFix,        ///< No valid GNSS fix available
    Autonomous,   ///< Standard autonomous GNSS fix
    DGPS,         ///< Differential GNSS fix
    RTKFloat,     ///< RTK float solution
    RTKFix        ///< RTK fixed solution
};

/**
 * @struct GnssQuality
 * @brief Represents the GNSS quality information of the simulator
 *
 * @details
 * This structure contains:
 *  - fix classification
 *  - HDOP
 *  - number of satellites used
 *
 * Additional quality fields can be added later, such as:
 *  - horizontal accuracy
 *  - vertical accuracy
 *  - heading accuracy
 */
struct GnssQuality
{
    FixType fix {FixType::NoFix};    ///< Current GNSS fix quality
    double hdop {99.9};              ///< Horizontal dilution of precision
    int satellitesUsed {0};          ///< Number of satellites used for solution
};

/**
 * @struct SimulatorState
 * @brief Central state container of the GNSS simulator
 *
 * @details
 * This structure is the single source of truth for the current simulation
 * state. All protocol encoders and output adapters shall use this model.
 */
struct SimulatorState
{
    std::chrono::system_clock::time_point utc;   ///< Current UTC timestamp
    GeoPosition position;                        ///< Current geographic position
    MotionState motion;                          ///< Current motion state
    GnssQuality quality;                         ///< Current GNSS quality state
};
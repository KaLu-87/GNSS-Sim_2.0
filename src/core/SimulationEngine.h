/******************************************************************************
 * @file        SimulationEngine.h
 * @brief       Core simulation engine for GNSS motion and position updates
 *
 * @details
 * The SimulationEngine advances the simulator state in fixed time steps.
 * It currently uses a local tangent plane / ENU-like approximation for
 * short-distance motion simulation.
 *
 * Responsibilities:
 *  - update UTC time
 *  - calculate traveled distance from speed and time step
 *  - project motion onto latitude/longitude
 *  - support reversing by inverting the movement vector
 *
 * @note
 * The current implementation is suitable for short-distance simulation and
 * test scenarios. It is not intended for high-precision geodetic simulation
 * over long distances.
 *
 * @warning
 * For long-duration or high-precision simulation, replace the current
 * projection with a proper forward geodesic model on WGS84.
 *
 * @author      KaLu-87
 * @date        2026-04-15
 ******************************************************************************/

#pragma once

#include "../domain/SimulatorState.h"
#include <cmath>
#include <chrono>

/**
 * @class SimulationEngine
 * @brief Advances the GNSS simulator state in deterministic time steps
 *
 * @details
 * The engine owns the internal SimulatorState and updates it every time
 * step via the step() function.
 */
class SimulationEngine
{
public:
    /**
     * @brief Constructs the simulation engine with default initial values
     *
     * @details
     * The current defaults are intended for development and testing only.
     */
    SimulationEngine()
    {
        m_state.utc = std::chrono::system_clock::now();
        m_state.position = {50.0, 8.0, 100.0};
        m_state.motion = {2.0, 90.0, 90.0, false};
        m_state.quality = {FixType::RTKFix, 0.8, 18};
    }

    /**
     * @brief Advances the simulator state by the specified time step
     *
     * @param dt Time step in seconds
     *
     * @details
     * This function:
     *  - updates the UTC timestamp
     *  - calculates effective speed
     *  - inverts the speed for reverse motion
     *  - calculates traveled distance
     *  - resolves motion into north/east components
     *  - updates latitude and longitude
     */
    void step(double dt)
    {
        m_state.utc = std::chrono::system_clock::now();

        double speed = m_state.motion.speed_mps;
        if (m_state.motion.reversing)
            speed *= -1.0;

        const double distance = speed * dt;
        const double courseRad = deg2rad(m_state.motion.course_over_ground_deg);

        const double dNorth = distance * std::cos(courseRad);
        const double dEast  = distance * std::sin(courseRad);

        const double latRad = deg2rad(m_state.position.lat_deg);

        const double dLat = dNorth / EarthRadiusM;
        const double dLon = dEast / (EarthRadiusM * std::cos(latRad));

        m_state.position.lat_deg += rad2deg(dLat);
        m_state.position.lon_deg += rad2deg(dLon);
    }

    /**
     * @brief Returns the current simulator state
     *
     * @return Constant reference to the internal SimulatorState
     */
    const SimulatorState& state() const { return m_state; }

private:
    static constexpr double EarthRadiusM = 6378137.0;   ///< Earth radius in meters
    SimulatorState m_state;                             ///< Internal simulator state

    /**
     * @brief Converts degrees to radians
     * @param deg Angle in degrees
     * @return Angle in radians
     */
    static double deg2rad(double deg) { return deg * M_PI / 180.0; }

    /**
     * @brief Converts radians to degrees
     * @param rad Angle in radians
     * @return Angle in degrees
     */
    static double rad2deg(double rad) { return rad * 180.0 / M_PI; }
};
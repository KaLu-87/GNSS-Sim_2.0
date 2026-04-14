#pragma once

#include "../domain/SimulatorState.h"
#include <cmath>
#include <chrono>

class SimulationEngine
{
public:
    SimulationEngine()
    {
        m_state.utc = std::chrono::system_clock::now();
        m_state.position = {50.0, 8.0, 100.0};
        m_state.motion = {2.0, 90.0, 90.0, false};
        m_state.quality = {FixType::RTKFix, 0.8, 18};
    }

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

    const SimulatorState& state() const { return m_state; }

private:
    static constexpr double EarthRadiusM = 6378137.0;
    SimulatorState m_state;

    static double deg2rad(double deg) { return deg * M_PI / 180.0; }
    static double rad2deg(double rad) { return rad * 180.0 / M_PI; }
};

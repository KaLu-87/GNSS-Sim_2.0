#pragma once

#include <chrono>

struct GeoPosition
{
    double lat_deg {0.0};
    double lon_deg {0.0};
    double alt_m {0.0};
};

struct MotionState
{
    double speed_mps {0.0};
    double course_over_ground_deg {0.0};
    double heading_deg_true {0.0};
    bool reversing {false};
};

enum class FixType
{
    NoFix,
    Autonomous,
    DGPS,
    RTKFloat,
    RTKFix
};

struct GnssQuality
{
    FixType fix {FixType::NoFix};
    double hdop {99.9};
    int satellitesUsed {0};
};

struct SimulatorState
{
    std::chrono::system_clock::time_point utc;
    GeoPosition position;
    MotionState motion;
    GnssQuality quality;
};

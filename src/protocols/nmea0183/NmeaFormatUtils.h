#pragma once

#include "../../domain/SimulatorState.h"
#include <QString>
#include <cmath>
#include <chrono>
#include <ctime>

namespace NmeaFormatUtils
{
    struct UtcFields
    {
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
    };

    inline UtcFields toUtcFields(const std::chrono::system_clock::time_point& tp)
    {
        const std::time_t t = std::chrono::system_clock::to_time_t(tp);

        std::tm utc {};
    #if defined(_WIN32)
        gmtime_s(&utc, &t);
    #else
        gmtime_r(&t, &utc);
    #endif

        return {
            utc.tm_year + 1900,
            utc.tm_mon + 1,
            utc.tm_mday,
            utc.tm_hour,
            utc.tm_min,
            utc.tm_sec
        };
    }

    inline QString formatUtcTimeHhmmss(const std::chrono::system_clock::time_point& tp)
    {
        const auto f = toUtcFields(tp);
        return QString("%1%2%3")
            .arg(f.hour,   2, 10, QChar('0'))
            .arg(f.minute, 2, 10, QChar('0'))
            .arg(f.second, 2, 10, QChar('0'));
    }

    inline QString formatUtcDateDdMmYy(const std::chrono::system_clock::time_point& tp)
    {
        const auto f = toUtcFields(tp);
        const int yy = f.year % 100;
        return QString("%1%2%3")
            .arg(f.day,   2, 10, QChar('0'))
            .arg(f.month, 2, 10, QChar('0'))
            .arg(yy,      2, 10, QChar('0'));
    }

    inline QString formatLat(double latDeg, QString& hemisphere)
    {
        hemisphere = (latDeg >= 0.0) ? "N" : "S";

        const double absDeg = std::abs(latDeg);
        const int degrees = static_cast<int>(std::floor(absDeg));
        const double minutes = (absDeg - static_cast<double>(degrees)) * 60.0;

        return QString("%1%2")
            .arg(degrees, 2, 10, QChar('0'))
            .arg(minutes, 7, 'f', 4, QChar('0'));
    }

    inline QString formatLon(double lonDeg, QString& hemisphere)
    {
        hemisphere = (lonDeg >= 0.0) ? "E" : "W";

        const double absDeg = std::abs(lonDeg);
        const int degrees = static_cast<int>(std::floor(absDeg));
        const double minutes = (absDeg - static_cast<double>(degrees)) * 60.0;

        return QString("%1%2")
            .arg(degrees, 3, 10, QChar('0'))
            .arg(minutes, 7, 'f', 4, QChar('0'));
    }

    inline QString formatDegrees1(double value)
    {
        return QString::number(value, 'f', 1);
    }

    inline QString formatKnotsFromMps(double mps)
    {
        constexpr double factor = 1.9438444924406;
        return QString::number(mps * factor, 'f', 1);
    }

    inline QString formatKmhFromMps(double mps)
    {
        return QString::number(mps * 3.6, 'f', 1);
    }

    inline QString fixTypeToGgaQuality(const FixType fix)
    {
        switch (fix)
        {
        case FixType::NoFix:       return "0";
        case FixType::Autonomous:  return "1";
        case FixType::DGPS:        return "2";
        case FixType::RTKFloat:    return "5";
        case FixType::RTKFix:      return "4";
        default:                   return "0";
        }
    }

    inline QString fixTypeToRmcStatus(const FixType fix)
    {
        return (fix == FixType::NoFix) ? "V" : "A";
    }
}

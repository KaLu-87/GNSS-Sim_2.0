/******************************************************************************
 * @file        NmeaChecksum.h
 * @brief       Utility for creating NMEA 0183 checksummed sentences
 *
 * @details
 * This helper creates complete NMEA 0183 sentences by:
 *  - calculating the XOR checksum
 *  - prepending '$'
 *  - appending '*XX'
 *  - appending CRLF
 *
 * @author      KaLu-87
 * @date        2026-04-15
 ******************************************************************************/

#pragma once

#include <QString>
#include <QByteArray>

/**
 * @class NmeaChecksum
 * @brief Helper class for NMEA 0183 checksum generation
 */
class NmeaChecksum
{
public:
    /**
     * @brief Adds NMEA checksum and sentence framing
     *
     * @param sentenceWithoutDollarAndStar Sentence body without '$' and checksum
     * @return Complete NMEA sentence including '$', checksum and CRLF
     */
    static QString addChecksum(const QString& sentenceWithoutDollarAndStar)
    {
        QByteArray bytes = sentenceWithoutDollarAndStar.toLatin1();
        unsigned char checksum = 0;

        for (char c : bytes)
        {
            checksum ^= static_cast<unsigned char>(c);
        }

        return QString("$%1*%2\r\n")
            .arg(sentenceWithoutDollarAndStar)
            .arg(checksum, 2, 16, QChar('0'))
            .toUpper();
    }
};
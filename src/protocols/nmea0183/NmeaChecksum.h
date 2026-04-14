#pragma once

#include <QString>
#include <QByteArray>

class NmeaChecksum
{
public:
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

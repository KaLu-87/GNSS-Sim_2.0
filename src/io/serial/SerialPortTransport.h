/******************************************************************************
 * @file        SerialPortTransport.h
 * @brief       Minimal serial transport wrapper for RS232 output
 *
 * @details
 * This transport encapsulates basic QSerialPort write access for sending
 * NMEA data over a serial interface.
 *
 * Responsibilities:
 *  - open a serial port
 *  - close a serial port
 *  - write raw byte streams
 *
 * @note
 * This is intentionally minimal. Error handling, retries and configuration
 * extensions can be added later.
 *
 * @author      KaLu-87
 * @date        2026-04-15
 ******************************************************************************/

#pragma once

#include <QObject>
#include <QSerialPort>

/*
 * @class SerialPortTransport
 * @brief Minimal RS232 transport wrapper
 */
class SerialPortTransport : public QObject
{
    Q_OBJECT

public:
    /*
     * @brief Opens the configured serial port
     *
     * @param portName Name of the COM/serial port
     * @param baudRate Baud rate to use
     * @return True if the port was opened successfully
     */
    bool open(const QString& portName, int baudRate)
    {
        m_port.setPortName(portName);
        m_port.setBaudRate(baudRate);
        return m_port.open(QIODevice::WriteOnly);
    }

    /*
     * @brief Closes the serial port if it is open
     */
    void close()
    {
        if (m_port.isOpen())
            m_port.close();
    }

    /*
     * @brief Writes raw bytes to the serial port
     *
     * @param data Byte array to be transmitted
     * @return True if bytes were accepted for writing
     */
    bool write(const QByteArray& data)
    {
        if (!m_port.isOpen())
            return false;

        return m_port.write(data) > 0;
    }

private:
    QSerialPort m_port;   ///< Underlying Qt serial port
};
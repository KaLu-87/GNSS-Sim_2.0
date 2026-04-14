#pragma once

#include <QObject>
#include <QSerialPort>

class SerialPortTransport : public QObject
{
    Q_OBJECT

public:
    bool open(const QString& portName, int baudRate)
    {
        m_port.setPortName(portName);
        m_port.setBaudRate(baudRate);
        return m_port.open(QIODevice::WriteOnly);
    }

    void close()
    {
        if (m_port.isOpen())
            m_port.close();
    }

    bool write(const QByteArray& data)
    {
        if (!m_port.isOpen())
            return false;

        return m_port.write(data) > 0;
    }

private:
    QSerialPort m_port;
};

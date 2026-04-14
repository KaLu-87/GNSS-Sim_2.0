#pragma once

#include "../../protocols/nmea0183/Nmea0183Encoder.h"
#include "SerialPortTransport.h"
#include "SerialOutputConfig.h"
#include "../IOutputAdapter.h"

class Nmea0183SerialOutputAdapter : public IOutputAdapter
{
public:
    Nmea0183SerialOutputAdapter(const SerialOutputConfig& config)
        : m_config(config)
    {}

    bool start() override
    {
        return m_transport.open(m_config.portName, m_config.baudRate);
    }

    void stop() override
    {
        m_transport.close();
    }

    void send(const SimulatorState& state) override
    {
        const auto sentences = m_encoder.encodeAll(state);

        for (const auto& s : sentences)
        {
            m_transport.write(s.toLatin1());
        }
    }

private:
    SerialOutputConfig m_config;
    SerialPortTransport m_transport;
    Nmea0183Encoder m_encoder;
};
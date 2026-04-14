#pragma once

#include "../core/SimulationEngine.h"
#include <QObject>
#include <QTimer>

class ApplicationController : public QObject
{
    Q_OBJECT

public:
    ApplicationController()
    {
        connect(&m_timer, &QTimer::timeout, this, &ApplicationController::onTick);
        m_timer.setInterval(100);
    }

    void start() { m_timer.start(); }
    void stop() { m_timer.stop(); }

signals:
    void stateUpdated(const SimulatorState& state);

private slots:
    void onTick()
    {
        m_engine.step(0.1);
        emit stateUpdated(m_engine.state());
    }

private:
    SimulationEngine m_engine;
    QTimer m_timer;
};

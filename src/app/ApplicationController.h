/******************************************************************************
 * @file        ApplicationController.h
 * @brief       Application-level controller for simulation execution
 *
 * @details
 * The ApplicationController coordinates the periodic execution of the
 * SimulationEngine and forwards updated simulator states to the UI and
 * output layers via Qt signals.
 *
 * Responsibilities:
 *  - own the SimulationEngine
 *  - provide start/stop control
 *  - execute simulation steps on a fixed interval
 *  - emit state updates to other layers
 *
 * @author      KaLu-87
 * @date        2026-04-15
 ******************************************************************************/

#pragma once

#include "../core/SimulationEngine.h"
#include <QObject>
#include <QTimer>

/**
 * @class ApplicationController
 * @brief Controls timer-driven simulation updates
 *
 * @details
 * This class connects a fixed Qt timer to the simulation engine and emits
 * updated states for UI display and output processing.
 */
class ApplicationController : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the application controller
     *
     * @details
     * The simulation timer is configured to 100 ms, corresponding to 10 Hz.
     */
    ApplicationController()
    {
        connect(&m_timer, &QTimer::timeout, this, &ApplicationController::onTick);
        m_timer.setInterval(100);
    }

    /**
     * @brief Starts the simulation loop
     */
    void start() { m_timer.start(); }

    /**
     * @brief Stops the simulation loop
     */
    void stop() { m_timer.stop(); }

signals:
    /**
     * @brief Emitted whenever a new simulator state is available
     *
     * @param state Current simulator state
     */
    void stateUpdated(const SimulatorState& state);

private slots:
    /**
     * @brief Executes one simulation step and emits the updated state
     */
    void onTick()
    {
        m_engine.step(0.1);
        emit stateUpdated(m_engine.state());
    }

private:
    SimulationEngine m_engine;   ///< Core simulation engine
    QTimer m_timer;              ///< Periodic timer driving the simulation
};
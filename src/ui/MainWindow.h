#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "../app/ApplicationController.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow()
    {
        auto* central = new QWidget(this);
        auto* layout = new QVBoxLayout(central);

        m_label = new QLabel(this);
        m_nmeaView = new QPlainTextEdit(this);
        m_nmeaView->setReadOnly(true);

        layout->addWidget(m_label);
        layout->addWidget(m_nmeaView);
        setCentralWidget(central);

        resize(1000, 700);
        setWindowTitle("GNSS Simulator 2.0");

        connect(&m_controller, &ApplicationController::stateUpdated,
                this, &MainWindow::updateDisplay);

        m_controller.start();
    }

private slots:
    void updateDisplay(const SimulatorState& state)
    {
        m_label->setText(QString(
            "Lat: %1\nLon: %2\nSpeed: %3 m/s\nCOG: %4°\nHDT: %5°")
            .arg(state.position.lat_deg, 0, 'f', 6)
            .arg(state.position.lon_deg, 0, 'f', 6)
            .arg(state.motion.speed_mps, 0, 'f', 2)
            .arg(state.motion.course_over_ground_deg, 0, 'f', 1)
            .arg(state.motion.heading_deg_true, 0, 'f', 1));
    }

private:
    QLabel* m_label {nullptr};
    QPlainTextEdit* m_nmeaView {nullptr};
    ApplicationController m_controller;
};

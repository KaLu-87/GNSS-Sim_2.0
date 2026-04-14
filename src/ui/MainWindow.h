#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QSerialPortInfo>

#include "../app/ApplicationController.h"
#include "../protocols/nmea0183/Nmea0183Encoder.h"
#include "../io/serial/Nmea0183SerialOutputAdapter.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow()
    {
        auto* central = new QWidget(this);
        auto* layout = new QVBoxLayout(central);

        m_stateLabel = new QLabel(this);
        m_nmeaView = new QPlainTextEdit(this);
        m_nmeaView->setReadOnly(true);

        m_portCombo = new QComboBox(this);
        m_baudCombo = new QComboBox(this);
        m_connectButton = new QPushButton("Connect", this);

        layout->addWidget(m_stateLabel);
        layout->addWidget(m_portCombo);
        layout->addWidget(m_baudCombo);
        layout->addWidget(m_connectButton);
        layout->addWidget(m_nmeaView);

        setCentralWidget(central);

        resize(1000, 700);

        // Baudraten
        m_baudCombo->addItems({"4800","9600","19200","38400","57600","115200"});
        m_baudCombo->setCurrentText("115200");

        refreshPorts();

        connect(m_connectButton, &QPushButton::clicked,
                this, &MainWindow::onConnect);

        connect(&m_controller, &ApplicationController::stateUpdated,
                this, &MainWindow::updateDisplay);

        m_controller.start();
    }

private slots:
    void onConnect()
    {
        SerialOutputConfig config;
        config.portName = m_portCombo->currentText();
        config.baudRate = m_baudCombo->currentText().toInt();

        m_adapter = std::make_unique<Nmea0183SerialOutputAdapter>(config);
        m_adapter->start();
    }

    void updateDisplay(const SimulatorState& state)
    {
        m_stateLabel->setText(QString(
            "Lat: %1\nLon: %2\nSpeed: %3 m/s\nCOG: %4°\nHDT: %5°")
            .arg(state.position.lat_deg, 0, 'f', 6)
            .arg(state.position.lon_deg, 0, 'f', 6)
            .arg(state.motion.speed_mps, 0, 'f', 2)
            .arg(state.motion.course_over_ground_deg, 0, 'f', 1)
            .arg(state.motion.heading_deg_true, 0, 'f', 1));

        const auto sentences = m_encoder.encodeAll(state);
        m_nmeaView->setPlainText(sentences.join(""));

        if (m_adapter)
            m_adapter->send(state);
    }

private:
    void refreshPorts()
    {
        m_portCombo->clear();

        for (const auto& port : QSerialPortInfo::availablePorts())
        {
            m_portCombo->addItem(port.portName());
        }
    }

    QLabel* m_stateLabel {nullptr};
    QPlainTextEdit* m_nmeaView {nullptr};
    QComboBox* m_portCombo {nullptr};
    QComboBox* m_baudCombo {nullptr};
    QPushButton* m_connectButton {nullptr};

    ApplicationController m_controller;
    Nmea0183Encoder m_encoder;
    std::unique_ptr<Nmea0183SerialOutputAdapter> m_adapter;
};
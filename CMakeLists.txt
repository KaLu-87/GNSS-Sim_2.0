cmake_minimum_required(VERSION 3.21)
project(GNSSSim2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets SerialPort SerialBus)

qt_standard_project_setup()

qt_add_executable(GNSSSim2
    src/main.cpp
    src/app/ApplicationController.h
    src/core/SimulationEngine.h
    src/domain/SimulatorState.h
    src/ui/MainWindow.h
    src/protocols/nmea0183/NmeaChecksum.h
    src/protocols/nmea0183/NmeaFormatUtils.h
    src/protocols/nmea0183/GgaEncoder.h
    src/protocols/nmea0183/RmcEncoder.h
    src/protocols/nmea0183/VtgEncoder.h
    src/protocols/nmea0183/HdtEncoder.h
    src/protocols/nmea0183/ZdaEncoder.h
    src/protocols/nmea0183/Nmea0183Encoder.h
    src/protocols/nmea0183/Nmea0183Encoder.cpp
)

target_link_libraries(GNSSSim2
    PRIVATE
    Qt6::Widgets
    Qt6::SerialPort
    Qt6::SerialBus
)

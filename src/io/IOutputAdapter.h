#pragma once
#include "../domain/SimulatorState.h"

class IOutputAdapter
{
public:
    virtual ~IOutputAdapter() = default;

    virtual bool start() = 0;
    virtual void stop() = 0;
    virtual void send(const SimulatorState& state) = 0;
};
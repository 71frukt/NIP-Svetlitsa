#pragma once

#include <Arduino.h>

namespace Esp32Soft
{

class ElectrogasDevice
{

public:
    ElectrogasDevice()          = default;
    virtual ~ElectrogasDevice() = default;

    void StartIgnition(uint8_t target_pow);
    void StopIgnition () { state_ = IDLE; }

    bool Update();

protected:
    virtual void ApplyHwBrightness(uint8_t pow) = 0;

private:
    enum State {
        IDLE,
        WARMUP,
        FLICKER_ON,
        FLICKER_OFF,
        STABILIZE
    };

    State state_ = IDLE;
    
    unsigned long last_update_   = 0;
    unsigned long step_duration_ = 0;

    uint8_t target_brightness_   = 0;
    uint8_t flicker_count_       = 0;
    int     current_pause_       = 0;

    void ProcessFsm();
};

}

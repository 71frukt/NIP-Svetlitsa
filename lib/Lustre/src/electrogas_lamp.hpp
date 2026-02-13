#pragma once

#include <Arduino.h>
#include "ipwm_module.hpp"

class ElectrogasLamp
{

public:
    ElectrogasLamp(IPwmModule& pwm_module)
        : pwm_module_(pwm_module)
    {}

    ~ElectrogasLamp() = default;

    void StartIgnition(uint8_t target_pow);
    
    void StopIgnition() 
    { 
        state_ = IDLE; 
        pow_ = 0;
    }

    bool Update();

    void SetBrightness(uint8_t pow)
    {
        pow_ = pow;
        pwm_module_.SetPower(pow_);
        
        // if (state_ != IDLE) 
        // {
        //      state_ = IDLE; 
        // }
    }

    [[nodiscard]] uint8_t GetBrightness() const
    {
        return pow_;
    }

private:

    uint8_t pow_;
    IPwmModule& pwm_module_;

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

    void ProcessFsm_();
};

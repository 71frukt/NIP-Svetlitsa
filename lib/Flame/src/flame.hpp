#pragma once

#include <Arduino.h>

#include "ipwm_module.hpp"

class Flame
{

public:
    Flame(IPwmModule& pwm_module)
        : pwm_module_(pwm_module)
    {}

    ~Flame() = default;

    void StartIgnition(uint8_t target_pow, uint8_t wind_strength = 30);
    
    void StopIgnition() 
    { 
        state_ = IDLE; 
        pow_ = 0;
    }

    bool Update();

    void SetPow(uint8_t pow)
    {
        pow_ = pow;

        pow_ = pow;
        pwm_module_.SetPower(pow_);
    }

    uint8_t GetPow() const
    {
        return pow_;
    }

    void SetWind(uint8_t wind)
    {
        wind_strength_ = wind;
    }


private:
    uint8_t pow_;
    const IPwmModule& pwm_module_;

    enum State {
        IDLE,
        IGNITION_SPARK,              // вспышка спички
        IGNITION_GAP,                // темнота между вспышками
        IGNITION_DIP,                // проседание перед разгоранием
        IGNITION_RAMP,               // плавный рост "тела" пламени
        BURNING                      // основной режим
    };

    State state_ = IDLE;
    
    unsigned long last_update_   = 0;
    unsigned long step_duration_ = 0; // время до следующего кадра анимации

    uint8_t target_brightness_   = 0;
    uint8_t wind_strength_       = 30; // сила дрожания

    uint8_t spark_count_         = 0;
    float   current_base_        = 0; 

    void ProcessFsm_();
    uint8_t CalculateFlicker_(uint8_t base_val);
};

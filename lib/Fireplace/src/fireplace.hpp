#pragma once

#include <Arduino.h>
#include <vector>
#include <Bounce2.h>

#include "flame.hpp"
#include "water_sensor.hpp"
#include "ipwm_module.hpp"

class Fireplace
{
public:
    Fireplace(IPwmModule& flame_pwm_module, const Bounce2::Button& smoke_btn, const WaterSensor& water_sensor)
        : flame_        (flame_pwm_module)
        , smoke_btn_    (smoke_btn)
        , water_sensor_ (water_sensor)
        // : smoke_pow_            (0)
        // , smoke_fire_delay_ms_  (300)
        // , smoke_update_interval_(30 )
        // , last_smoke_update_    (0  )
        // , smoke_buffer_(smoke_fire_delay_ms_ / smoke_update_interval_)
    {

    }

    void StartIgnition(uint8_t target_pow, uint8_t wind_strength = 30)
    {
        flame_.StartIgnition(target_pow, wind_strength);
    }

    void SetPow(uint8_t pow)
    {
        flame_.SetPow(pow);
    }

    [[nodiscard]] uint8_t GetFlamePow () const { return flame_.GetPow(); }
    [[nodiscard]] bool    FlameEnabled() const { return state_ == FLAME_FIRE_AND_SMOKE; }
    
    // uint8_t GetSmokePow() { return smoke_pow_;     }

    void Update();

private:
    Flame flame_;

    enum State
    {
        FLAME_FIRE_ONLY     ,
        FLAME_FIRE_AND_SMOKE
    };

    State state_;

    const Bounce2::Button& smoke_btn_;
    const WaterSensor    & water_sensor_;
    

};

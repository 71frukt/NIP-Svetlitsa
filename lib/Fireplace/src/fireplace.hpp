#pragma once

#include <Arduino.h>
#include <vector>

#include "flame.hpp"
#include "ipwm_module.hpp"

class Fireplace
{
public:
    Fireplace(IPwmModule& flame_pwm_module)
        : flame_(flame_pwm_module)
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

    uint8_t GetFlamePow() const { return flame_.GetPow(); }
    // uint8_t GetSmokePow() { return smoke_pow_;     }

    void Update();

private:
    Flame flame_;
    // uint8_t smoke_pow_;

    // const uint32_t smoke_fire_delay_ms_;       // задержка дыма
    // const uint32_t smoke_update_interval_;     // дискретизация (33 FPS)
    // unsigned long  last_smoke_update_;    

    // // кольцевой буфер
    // std::vector<uint8_t> smoke_buffer_;
    // size_t head_ = 0;

};

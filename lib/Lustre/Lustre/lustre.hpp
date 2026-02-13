#pragma once

#include <Arduino.h>

#include "electrogas_device.hpp"
#include "PwmModule/pwm_module.hpp"

namespace Esp32Soft
{

class Lustre : public ElectrogasDevice
{
public:
    Lustre() = default;
    
    // Lustre(uint8_t pin, uint8_t  pwm_channel, uint32_t pwm_freq = 5000, uint8_t pwm_resolution = 8)
    //     : pwm_module(pin, pwm_channel, pwm_freq, pwm_resolution)
    // {
    //     outpin_.SetPower(0);
    // }

    void SetBrightness(uint8_t pow)
    {
        brightness = pow;
    }

    void ApplyHwBrightness(uint8_t pow) override
    {
        SetBrightness(pow);
    }

private:
    uint8_t brightness;
    
};

}
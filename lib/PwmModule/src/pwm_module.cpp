#include <Arduino.h>

#include "PwmModule/pwm_module.hpp"

namespace Esp32Soft
{

PwmModule::PwmModule(uint8_t pin, uint8_t  pwm_channel, uint32_t pwm_freq, uint8_t pwm_resolution)
        : pin_             (pin)
        , pwm_channel_     (pwm_channel)
        , pwm_freq_        (pwm_freq)
        , pwm_resolution_  (pwm_resolution)
        , max_duty_        ((1 << pwm_resolution) - 1)
{
    ledcSetup(pwm_channel_, pwm_freq_, pwm_resolution_);
    ledcAttachPin(pin_, pwm_channel_);
    SetBrightness(0);
}

void PwmModule::SetPower(uint8_t percentage)
{
    if (percentage > 100)
        percentage = 100;

    uint32_t duty = (percentage * max_duty_) / 100;
    
    ledcWrite(pwm_channel_, duty);
}

}
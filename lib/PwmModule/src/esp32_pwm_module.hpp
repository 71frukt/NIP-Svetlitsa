#include <Arduino.h>

#include "ipwm_module.hpp"

namespace Esp32Soft
{

class PwmModule : public IPwmModule
{
public:
    PwmModule(uint8_t pin, uint8_t pwm_channel, uint32_t pwm_freq = 5000, uint8_t pwm_resolution = 8)
        : cur_pow_         (0)
        , max_pow_         (100)
        , pin_             (pin)
        , pwm_channel_     (pwm_channel)
        , pwm_freq_        (pwm_freq)
        , pwm_resolution_  (pwm_resolution)

        , max_duty_        ((1 << pwm_resolution) - 1)
    {
        ledcSetup(pwm_channel_, pwm_freq_, pwm_resolution_);
        ledcAttachPin(pin_, pwm_channel_);
        SetPower(0);
    }

    void SetPower(uint8_t pow) override
    {
        if (pow > 100)
            pow = 100;

        uint32_t duty = ((uint32_t)pow * max_duty_ * max_pow_) / 100 / 100;
        
        ledcWrite(pwm_channel_, duty);
    }

    [[nodiscard]] uint8_t GetCurPower() const
    {
        return cur_pow_;
    }

    void SetMaxPower(uint8_t max_pow)
    {
        if (max_pow > 100)
            max_pow_ = 100;

        else
            max_pow_ = max_pow;
    }
    
    [[nodiscard]] uint8_t GetMaxPower() const
    {
        return max_pow_;
    }

private:
    uint8_t  cur_pow_;
    uint8_t  max_pow_;

    const uint8_t  pin_;
    const uint8_t  pwm_channel_;
    const uint32_t pwm_freq_;
    const uint8_t  pwm_resolution_;

    const uint32_t max_duty_;
};

}
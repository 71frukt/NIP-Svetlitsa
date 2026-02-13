#include <Arduino.h>

namespace Esp32Soft
{

class PwmModule
{
public:
    PwmModule(uint8_t pin, uint8_t pwm_channel, uint32_t pwm_freq = 5000, uint8_t pwm_resolution = 8);

    void SetPower(uint8_t percentage)
    {
        if (percentage > 100)
            percentage = 100;

        uint32_t duty = (percentage * max_duty_) / 100;
        
        ledcWrite(pwm_channel_, duty);
    }

private:
    const uint8_t  pin_;
    const uint8_t  pwm_channel_;
    const uint32_t pwm_freq_;
    const uint8_t  pwm_resolution_;
    const uint32_t max_duty_;
};

}
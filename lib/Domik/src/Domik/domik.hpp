#include <Arduino.h>

#include "Lustre/lustre.hpp"

namespace Esp32Soft
{

class Domik
{
public:
    Domik(uint8_t lustre_pin, uint8_t lustre_pwm_channel,
          uint32_t pwm_freq = 5000, uint8_t pwm_resolution = 8)

        : lustre(lustre_pin, lustre_pwm_channel)
    {

    }

    void Update()
    {
        lustre.Update();
    }

    Lustre lustre;
    
private:

};

}
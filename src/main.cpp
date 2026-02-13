#include <Arduino.h>

#include "electrogas_lamp.hpp"
#include "ipwm_module.hpp"
#include "esp32_pwm_module.hpp"

Esp32Soft::PwmModule lamp_pwm{14, 0}; // Пин 14, канал 0
ElectrogasLamp lamp(lamp_pwm);

void setup()
{
    Serial.begin(115200);

    lamp.StartIgnition(100);
}

void loop() {
    lamp.Update();
}

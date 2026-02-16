#include <Arduino.h>

#include "electrogas_lamp.hpp"
#include "ipwm_module.hpp"
#include "esp32_pwm_module.hpp"

Esp32Soft::PwmModule lamp_pwm{14, 0}; // Пин 14, канал 0
ElectrogasLamp lamp(lamp_pwm);

void setup()
{
    Serial.begin(115200);
    
    analogReadResolution(12); // 0-4095
    analogSetAttenuation(ADC_11db); // Читаем весь диапазон 0-3.3В
    
    lamp.StartIgnition(100);
}

void loop() {
    lamp.Update();

    // if no smoke - disable water_sensor
}

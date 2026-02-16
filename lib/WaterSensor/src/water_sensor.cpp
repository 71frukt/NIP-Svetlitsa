#include <Arduino.h>

#include "water_sensor.hpp"

void WaterSensor::Update()
{
    if (enabled_ == false)
    {
        return;
    }

    unsigned long current_millis = millis();

    if (!is_measuring_ && (current_millis - last_measure_time_ >= measure_period_s_ * 1000UL))
    {
        digitalWrite(power_pin_, HIGH);
        
        is_measuring_ = true;
        
        warmup_start_time_ = current_millis;
    }

    if (is_measuring_)
    {
        if (current_millis - warmup_start_time_ >= SENSOR_WARMUP_MS)
        {
            water_hight_ = analogRead(sensor_pin_);

            // выключаем датчик (чтобы не гнил)
            digitalWrite(power_pin_, LOW);

            is_measuring_ = false;
            last_measure_time_ = current_millis;
        }
    }
}
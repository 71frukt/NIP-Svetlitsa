#include "Lustre/electrogas_device.hpp"

namespace Esp32Soft
{

void ElectrogasDevice::StartIgnition(uint8_t target_pow)
{
    if (target_pow > 100) target_pow = 100;
    
    target_brightness_ = target_pow;
    flicker_count_     = random(3, 7);
    current_pause_     = 400; 

    state_         = WARMUP;
    step_duration_ = random(200, 600);
    last_update_   = millis();

    // Устанавливаем начальное "тление" через виртуальный метод
    ApplyHwBrightness(10); 
}

bool ElectrogasDevice::Update()
{
    if (state_ == IDLE)
        return false;

    unsigned long current_millis = millis();

    if (current_millis - last_update_ >= step_duration_)
    {
        last_update_ = current_millis;
        ProcessFsm();
    }
    return true;
}   

void ElectrogasDevice::ProcessFsm()
{
    switch (state_)
    {
    case WARMUP:
        state_ = FLICKER_ON;
        step_duration_ = random(20, 80);
        ApplyHwBrightness(random(50, 101));
        break;

    case FLICKER_ON:
        state_ = FLICKER_OFF;
        step_duration_ = current_pause_;
        ApplyHwBrightness(0);

        current_pause_ = (current_pause_ * random(60, 80)) / 100;
        if (current_pause_ < 20) current_pause_ = 20;
        break;

    case FLICKER_OFF:
        flicker_count_--;
        if (flicker_count_ > 0)
        {
            state_ = FLICKER_ON;
            step_duration_ = random(20, 80);
            ApplyHwBrightness(random(50, 101));
        }

        else
        {
            state_ = STABILIZE;
            step_duration_ = 150;
            ApplyHwBrightness(target_brightness_ * 0.8);
        }
        break;

    case STABILIZE:
        state_ = IDLE;
        ApplyHwBrightness(target_brightness_);
        break;

    case IDLE:
    default:
        break;
    }
}

}
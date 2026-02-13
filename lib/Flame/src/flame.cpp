#include <Arduino.h>

#include "flame.hpp"

void Flame::StartIgnition(uint8_t target_pow, uint8_t wind_strength)
{
    if (target_pow > 100) target_pow = 100;

    target_brightness_ = target_pow;
    wind_strength_     = wind_strength;
    
    spark_count_   = random(1, 4); // 1-3 попытки "чиркнуть"
    current_base_  = 0;
    
    state_         = IGNITION_SPARK;
    step_duration_ = 0;            // Первый кадр сразу
    last_update_   = millis();
}

bool Flame::Update()
{
    if (state_ == IDLE)
        return false;

    unsigned long current_millis = millis();

    if (current_millis - last_update_ >= step_duration_)
    {
        last_update_ = current_millis;
        ProcessFsm_();
    }

    return true;
}

void Flame::ProcessFsm_()
{
    switch (state_)
    {
    case IGNITION_SPARK:
        // резкая вспышка (искра)
        pow_ = 40;
        step_duration_ = random(20, 50);
        
        spark_count_--;

        if (spark_count_ == 0) 
        {
            state_ = IGNITION_DIP; // Искры кончились -> уходим в затухание
        }
        
        else 
        {
            state_ = IGNITION_GAP; // Искры есть -> нужна пауза темноты
        }

        break;

    case IGNITION_GAP:
        // Пауза между искрами (Темнота)
        pow_ = 0; 
        step_duration_ = random(50, 150); // Пауза чуть длиннее самой искры
        
        // Возвращаемся к следующей искре
        state_ = IGNITION_SPARK;
        break;

    case IGNITION_DIP:
        // Провал яркости (почти погасло)
        pow_ = random(0, 10);
        step_duration_ = random(100, 300); // Пауза перед тем как фитиль схватится
        
        current_base_ = 5.0; // Начинаем разгораться с 5%
        state_ = IGNITION_RAMP;
        break;

    case IGNITION_RAMP:
        // Линейный рост "тела" огня
        current_base_ += 0.8; 
        
        if (current_base_ >= target_brightness_)
        {
            current_base_ = target_brightness_;
            state_ = BURNING;
        }

        // Даже при росте накладываем эффект огня
        pow_ = CalculateFlicker_((uint8_t)current_base_);
        step_duration_ = random(30, 80); 
        break;

    case BURNING:
        // Основной режим
        pow_ = CalculateFlicker_(target_brightness_);
        step_duration_ = random(40, 120); // Живой тайминг кадров
        break;

    case IDLE:
    default:
        break;
    }
}

uint8_t Flame::CalculateFlicker_(uint8_t base_val)
{
    // Субтрактивный алгоритм: из базы вычитаем случайную "тень" (ветер)
    int noise = random(0, wind_strength_);
    
    // Редкие всплески вверх (кислород)
    if (random(0, 20) == 0) { 
        noise = -random(0, wind_strength_ / 2); 
    }

    int result = base_val - noise;

    // Ограничение диапазона (Clamp)
    if (result < 0) result = 0;
    if (result > 100) result = 100;

    // Редкие провалы (сильный порыв ветра)
    if (random(0, 100) > 98) result /= 2;

    return (uint8_t)result;
}
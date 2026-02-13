#include "fireplace.hpp"

void Fireplace::Update()
{
    flame_.Update();

    smoke_pow_ = flame_.GetPow();

    // задержка дыма
    // unsigned long current_millis = millis();

    // if (current_millis - last_smoke_update_ >= smoke_update_interval_)
    // {
    //     last_smoke_update_ = current_millis;

    //     smoke_pow_ = smoke_buffer_[head_];

    //     smoke_buffer_[head_] = flame_.GetPow();

    //     // В. Сдвигаем индекс головы
    //     head_++;
    //     if (head_ >= smoke_buffer_.size())
    //     {
    //         head_ = 0;
    //     }
    // }
}
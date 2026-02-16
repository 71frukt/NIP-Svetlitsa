#include "fireplace.hpp"

void Fireplace::Update()
{
    flame_.Update();

    if (smoke_btn_.changed())
    {
        if (smoke_btn_.isPressed())
        {
            if (water_sensor_.GetWaterLvl() == WaterSensor::WATER_DRY)
            {
                state_ = FLAME_FIRE_ONLY;
            }

            else
            {
                state_ = FLAME_FIRE_AND_SMOKE;
            }
        }
        
        else
        {
            state_ = FLAME_FIRE_ONLY;
        }
    }


    if (state_ = FLAME_FIRE_AND_SMOKE)
    {
        // enable parogenerator;
    }
}
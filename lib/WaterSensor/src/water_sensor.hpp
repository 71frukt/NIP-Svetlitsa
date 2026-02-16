#include <Arduino.h>

class WaterSensor
{
public:
    WaterSensor(const uint8_t power_pin, const uint8_t sensor_pin, const uint32_t measure_period_s = 30)
        : power_pin_        (power_pin)
        , sensor_pin_       (sensor_pin)
        , measure_period_s_ (measure_period_s)
    {
        pinMode(power_pin, OUTPUT);
        digitalWrite(power_pin, LOW);

       
    }

    void Enable () { enabled_ = true;  }
    void Disable() { enabled_ = false; }

    void SetMeasurePeriod(const int period_s)
    {
        measure_period_s_ = period_s;
    }

    enum WaterLvl
    {
        WATER_DRY,
        WATER_LOW,
        WATER_MIDDLE,
        WATER_HIGH
    };

    [[nodiscard]] WaterLvl GetWaterLvl() const
    {
        if (enabled_ == false)
            return WATER_DRY;

        if (water_hight_ < 100)
            return WATER_DRY;

        else if (water_hight_ >= 100 && water_hight_ < 1500)
            return WATER_LOW;

        else if (water_hight_ >= 1500 && water_hight_ < 2500)
            return WATER_MIDDLE;

        else
            return WATER_HIGH;
    }

    void Update();

private:
    bool enabled_ = true;

    const uint8_t sensor_pin_;
    const uint8_t power_pin_ ;

    uint32_t water_hight_;


    unsigned long last_measure_time_ = 0;
    unsigned long warmup_start_time_ = 0;
    bool is_measuring_ = false;
    
    uint32_t measure_period_s_;
    static const uint32_t SENSOR_WARMUP_MS = 50;
};
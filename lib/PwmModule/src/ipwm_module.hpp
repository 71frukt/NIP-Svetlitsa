#include <Arduino.h>

class IPwmModule
{
public:
    virtual ~IPwmModule() = default;

    virtual void SetPower(uint8_t percentage) = 0;
};

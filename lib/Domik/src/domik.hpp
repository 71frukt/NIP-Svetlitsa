#include <Arduino.h>

#include "electrogas_lamp.hpp"
#include "fireplace.hpp"


class Domik
{
public:
    Domik()  = default;
    ~Domik() = default;

    void Update()
    {
        electrogas_lamp.Update();
        fireplace      .Update();
    }
    
private:
    ElectrogasLamp electrogas_lamp;
    Fireplace      fireplace;

};
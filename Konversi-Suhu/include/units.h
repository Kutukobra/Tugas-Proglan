#pragma once
#define UNIT_COUNT 4

enum UNIT_TYPE
{
    UNIT_CELCIUS,
    UNIT_RANKINE,
    UNIT_KELVIN,
    UNIT_FAHRENHEIT
};

struct UNIT_CELCIUS;

float convertTemperature(float input, enum UNIT_TYPE inputType, enum UNIT_TYPE outputType);
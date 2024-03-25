enum UNIT_TYPE
{
    UNIT_CELCIUS,
    UNIT_RANKINE,
    UNIT_KELVIN,
    UNIT_FAHRENHEIT
};

char *UNITS_NAME[] = 
{
    "CELCIUS",
    "RANKINE",
    "KELVIN",
    "FAHRENHEIT"
};


struct UNIT_CELCIUS
{   // Water based, scale = boiling - freezing
    float freezing, boiling, scale;
    char *name, *unit;
};

const struct UNIT_CELCIUS UNITS[] = {
    {   // Celcius
        0,
        99.9839,
        99.9839,
        "Celcius",
        "C"     
    },
    {   // Rankine
        491.67,
        671.64102,
        179.97102,
        "Rankine",
        "R"
    },  
    {   // Kelvin
        273.15,
        373.1339,
        99.9839,
        "Kelvin",
        "K"
    },
    {   // Fahrenheit
        32.00,
        211.97102,
        179.97102,
        "Fahrenheit",
        "F"
    }
};

float convertTemperature(float input, enum UNIT_TYPE inputType, enum UNIT_TYPE outputType)
{
    return (input - UNITS[inputType].freezing) * (UNITS[outputType].scale / UNITS[inputType].scale) + UNITS[outputType].freezing;
}
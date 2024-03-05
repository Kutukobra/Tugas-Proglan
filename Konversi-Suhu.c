#include <stdio.h>

enum UNIT_TYPE
{
    UNIT_CELCIUS,
    UNIT_RANKINE,
    UNIT_KELVIN,
    UNIT_FAHRENHEIT
};

#define UNIT_COUNT 4

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

void temperatureSelection()
{
    printf("| 1. Celcius             |\n");
    printf("| 2. Rankine             |\n");
    printf("| 3. Kelvin              |\n");
    printf("| 4. Fahrenheit          |\n");
    printf("|========================|\n");
    printf("\n> ");
}

float convertTemperature(float input, enum UNIT_TYPE inputType, enum UNIT_TYPE outputType)
{
    return (input - UNITS[inputType].freezing) * (UNITS[outputType].scale / UNITS[inputType].scale) + UNITS[outputType].freezing;
}

void mainMenu(enum UNIT_TYPE inputType, float inputData, enum UNIT_TYPE outputType, float outputData)
{
    system("clear");
    printf("|=TEMPERATURE CONVERSION=|\n");
    printf("| 1. Change Input Value  |\n");
    printf("| 2. Change Input Scale  |\n");
    printf("| 3. Change Output Scale |\n");
    printf("| 4. Help                |\n");
    printf("|========================|\n");

    printf("| %-10s > %10s|\n", UNITS[inputType].name, UNITS[outputType].name);
    printf("| %-7.2f %-2s > %7.2f %-2s|\n", inputData, UNITS[inputType].unit, outputData, UNITS[outputType].unit);

    printf("|========================|\n");
    
    printf("\n> ");
}

void help()
{
    printf("TEMPERATURE CONVERSION - Converts the input value according to the input and output temperature scales\n");
    printf(" 1. Change the input value of the conversion.\n");
    printf(" 2. Change the input temperature scale of conversion.\n");
    printf(" 3. Change the output temperature scale of conversion.\n");
    printf(" 4. Display this help menu\n");
    printf("\n\nThis program converts the scales with water boiling and freezing points at standard pressure.\n");
    printf("Formula: \n");
    printf("==========================================================================================\n");
    printf("|                 ([INPUT VALUE] - [INPUT FREEZING]) * [OUTPUT SCALE] + [OUTPUT FREEZING]|\n");
    printf("|[OUTPUT VALUE] =                                      --------------                    |\n");
    printf("|                                                       [INPUT SCALE]                    |\n");
    printf("==========================================================================================\n");
    system("pause");
}

int main()
{
    unsigned int option = 0;

    enum UNIT_TYPE inputType = 0, outputType = 0;
    float inputData, outputData;
    
    while (option != EOF)
    {
        outputData = convertTemperature(inputData, inputType, outputType);

        mainMenu(inputType, inputData, outputType, outputData);
        scanf("%d", &option);

        system("clear");
        switch (option)
        {
            enum UNIT_TYPE unitSelect;
            case 1:
                printf("=Input the new value=\n\n> ");
                scanf("%f", &inputData);
                break;
            
            case 2:
                printf("|====Select New Input====|\n");
                printf("|====Temperature Scale===|\n");
                temperatureSelection();
                scanf("%u", &unitSelect);
                if (unitSelect < 0 || unitSelect > UNIT_COUNT)
                {
                    perror("INVALID OPTION!");
                    break;
                }
                inputType = unitSelect - 1;
                break;
            
            case 3:
                printf("|====Select New Output===|\n");
                printf("|====Temperature Scale===|\n");
                temperatureSelection();
                scanf("%u", &unitSelect);
                if (unitSelect < 0 || unitSelect > UNIT_COUNT)
                {
                    perror("INVALID OPTION!");
                    break;
                }
                outputType = unitSelect - 1;
                break;
            
            case 4:
                help();
                break;
            
            default:
                printf("INVALID OPTION!\n");
        }
    }

    return 0;
}
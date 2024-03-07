#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#if defined(_WIN32)
#define CLEAR "cls"
#elif defined(unix)
#define CLEAR "clear"
#endif


#define ACCOUNT_MAX 10

typedef struct Account
{
    char email[32];
    char password[32];
    char token[32];
    int tokens;
} Account;

int accountCreate(Account *accountList)
{
    static int accountCount = 0;


    if (accountCount >= ACCOUNT_MAX)
    {
        return -1; // Error: Max Users
    }
    
    printf("|====Register Account====|\n");
    printf("EMAIL: ");
    scanf("%s", accountList[accountCount].email);
    printf("Password: ");
    scanf("%s", accountList[accountCount].password);

    return ++accountCount;
}

void accountLogin(Account *accounts, int *currentAccount)
{
    char email[32];
    char password[32];

    printf("|======Account Login=====|\n");
    printf("EMAIL: ");
    scanf("%s", email);
    printf("Password: ");
    scanf("%s", password);

    for (int i = 0; i < ACCOUNT_MAX; i++)
    {
        if (strcmp(email, accounts[i].email) == 0)
        {
            if (strcmp(password, accounts[i].password) == 0)
            {
                *currentAccount = i;
                return;
            }
            else
            {
                break;
            }
        }
    }
    printf("Wrong EMAIL OR PASSWORD!");
    getchar();getchar();
}

void accountLogout(bool *loggedIn, int *currentAccount) {
    *loggedIn = false;
    *currentAccount = -1; // Reset to invalid index
    printf("Logged out successfully.\n");
    getchar(); getchar(); // Pause
}

void handleTokenInput(Account *account) {
    if (account->tokens >= 10) {
        printf("Token maksimal 10, masukkan token baru! ");
        scanf("%s", account->tokens);
        account->tokens = 0; 
    } else {
        printf("You have %d conversions left.\n", 10 - account->tokens);
    }
}
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

void mainMenu(enum UNIT_TYPE inputType, float inputData, enum UNIT_TYPE outputType, float outputData, bool converted, bool loggedIn, int userID, Account *accounts)
{
    system(CLEAR);
    printf("|=TEMPERATURE CONVERSION=|%s\n", loggedIn ? accounts[userID].email : "");
    printf("| 1. Change Input Value  |\n");
    printf("| 2. Change Input Scale  |\n");
    printf("| 3. Change Output Scale |\n");
    printf("| 4. Convert Value       |\n");
    printf("| 5. %-8s            |\n", loggedIn ? "Logout" : "Login");
    if (loggedIn) {
    printf("| 6. Input Token         |\n");
    }
    printf("| 7. Register Account    |\n");
    printf("| 8. Help                |\n");
    printf("|========================|\n");

    printf("| %-10s > %10s|\n", UNITS[inputType].name, UNITS[outputType].name);
    
    if (converted)
        printf("| %-7.2f %-2s > %7.2f %-2s|\n", inputData, UNITS[inputType].unit, outputData, UNITS[outputType].unit);
    else
        printf("| %-7.2f %-2s >  _ _ _  %-2s|\n", inputData, UNITS[inputType].unit, UNITS[outputType].unit);

    printf("|========================|\n");
    
    printf("\n> ");
}

void help()
{
    printf("TEMPERATURE CONVERSION - Converts the input value according to the input and output temperature scales\n");
    printf(" 1. Change the input value of the conversion.\n");
    printf(" 2. Change the input temperature scale of conversion.\n");
    printf(" 3. Change the output temperature scale of conversion.\n");
    printf(" 4. Converts the value.\n");
    printf(" 5. Display this help menu\n");
    printf("\n\nThis program converts the scales with water boiling and freezing points at standard pressure.\n");
    printf("Formula: \n");
    printf("==========================================================================================\n");
    printf("|                 ([INPUT VALUE] - [INPUT FREEZING]) * [OUTPUT SCALE] + [OUTPUT FREEZING]|\n");
    printf("|[OUTPUT VALUE] =                                      --------------                    |\n");
    printf("|                                                       [INPUT SCALE]                    |\n");
    printf("==========================================================================================\n");
    int c = getchar();getchar();
}

int main()
{
    unsigned int option = 0;

    enum UNIT_TYPE inputType = 0, outputType = 0;
    float inputData, outputData;
    
    Account accounts[ACCOUNT_MAX] = {{0}};

    bool hasConverted = false, loggedIn = false;
	int currentAccount = -1;
	 
    while (1)
    {

        mainMenu(inputType, inputData, outputType, outputData, hasConverted, loggedIn, currentAccount, accounts);
        scanf("%d", &option);

        system(CLEAR);

        hasConverted = false;
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
                if (loggedIn && accounts[currentAccount].tokens >= 10) {
                    printf("Token limit reached, please enter a new token.\n");
                    scanf("%s", accounts[currentAccount].token); // Simplistic approach; consider unique token validation in a real scenario
                    accounts[currentAccount].tokens = 0; // Reset tokens after entering a new token
                }
                if (loggedIn) {
                    accounts[currentAccount].tokens++; // Increment token usage
                }
                outputData = convertTemperature(inputData, inputType, outputType);
                hasConverted = true;
                break;;

            case 5: 
                if (!loggedIn) {
                    accountLogin(accounts, &currentAccount);
                    loggedIn = currentAccount >= 0; // Update loggedIn based on successful login
                } else {
                    accountLogout(&loggedIn, &currentAccount);
                }
                break;
            case 6: 
                if (loggedIn) {
                    printf("Please enter your conversion token: ");
                    scanf("%s", accounts[currentAccount].token);
                    accounts[currentAccount].tokens = 0; // Assume new token provides a fresh set of conversions
                } else {
                    printf("You must be logged in to update your conversion token.\n");
                }
                break;
            
            case 7:
                accountCreate(accounts);
                break;

            case 8:
                help();
                break;
            
            default:
                printf("INVALID OPTION!\n");
        }
    }

    return 0;
}

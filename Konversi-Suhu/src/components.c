#include <windows.h>
#include <stdio.h>
#include "units.h"
#include "components.h"

HWND hmain;
HWND convertButton;

HWND inputField;
HWND outputField;

HWND inputDDown;
HWND outputDDown;

HWND accountButton;

HWND loginPage;

HWND hUsername;
HWND hPassword;

extern char *UNITS_NAME[];

enum UNIT_TYPE inputType = 0, outputType = 0;

int tokens;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LoginProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

typedef struct Dimension
{
    int x, y, width, height;
} Dimension;

Dimension TEXTBOX = {0, 0, 120, 20};
Dimension DROPDOWN = {0, 0, 120, 300};

void DisplayTemperature()
{
    if (tokens <= 0)
    {
        MessageBox(hmain, "Insufficent Tokens", "Failure", MB_ICONWARNING | MB_OK);
        return;
    }

    char buffer[256];
    GetWindowText(inputField, buffer, sizeof(buffer));
    float inputTemperature; 
    sscanf(buffer, "%f", &inputTemperature);
    sprintf(buffer, "%.2f", convertTemperature(inputTemperature, inputType, outputType));
    SetWindowText(outputField, buffer);

    --tokens;
}


void AddDropUnits(HWND dropdown, int IO)
{
    for (int i = 0; i < UNIT_COUNT; i++)
    {
        SendMessage(dropdown, CB_ADDSTRING, 0, (LPARAM)UNITS_NAME[i]);
    }
    SendMessage(dropdown, CB_SETCURSEL, IO, 0);
}


void WindowsSetup(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const char MAIN_WINDOW_CLASS[] = "MainWindowClass";

    WNDCLASS wcmain = {};
    wcmain.lpfnWndProc = WindowProc;
    wcmain.hInstance = hInstance;
    wcmain.lpszClassName = MAIN_WINDOW_CLASS;

    const char LOGIN_WINDOW[] = "LoginWindowClass";

    WNDCLASS wclogin = {};
    wclogin.lpfnWndProc = LoginProc;
    wclogin.hInstance = hInstance;
    wclogin.lpszClassName = LOGIN_WINDOW;
    
    RegisterClass(&wclogin);
    
    RegisterClass(&wcmain);

    hmain = CreateWindow(
        MAIN_WINDOW_CLASS, // Window class name
        "Temperature Converter", // Window name
        WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX, // Window Styles
        CW_USEDEFAULT, CW_USEDEFAULT, 340, 200, // Window Dimensions
        NULL, // Parent Window Handle
        NULL, // Menu Handle
        hInstance, // Handle Instance
        NULL // lp Param
    );

    convertButton = CreateWindow(
        "BUTTON",
        "CONVERT!",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        130, 19, 75, 50,
        hmain,
        (HMENU) IDCHANGE,
        hInstance,
        NULL
    );

    accountButton = CreateWindow(
        "BUTTON",
        "LOGIN",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        10, 70, 300, 30,
        hmain,
        (HMENU) IDLOGIN,
        hInstance,
        NULL
    );
    

    inputField = CreateWindow(
        "EDIT",
        "",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        5, 20, TEXTBOX.width, TEXTBOX.height,
        hmain,
        NULL,
        hInstance,
        NULL
    );

    inputDDown = CreateWindow(
        "COMBOBOX",
        "",
        CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE,
        5, 43, DROPDOWN.width, DROPDOWN.height,
        hmain,
        (HMENU) IDINPUT,
        hInstance,
        NULL
    );

    AddDropUnits(inputDDown, inputType);

    outputField = CreateWindow(
        "STATIC",
        "TEMP",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        210, 20, TEXTBOX.width, TEXTBOX.height,
        hmain,
        NULL,
        hInstance,
        NULL
    );

    outputDDown = CreateWindow(
        "COMBOBOX",
        "",
        CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE,
        210, 43, DROPDOWN.width, DROPDOWN.height,
        hmain,
        (HMENU) IDOUTPUT,
        hInstance,
        NULL
    );

    

    
    AddDropUnits(outputDDown, outputType);
    ShowWindow(hmain, nCmdShow);    
}
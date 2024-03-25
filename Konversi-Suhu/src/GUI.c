#include <windows.h>
#include "units.h"
#include "components.h"
#include <stdio.h>


extern HWND hmain;
extern HWND convertButton;
extern HWND accountButton;

extern HWND inputField;
extern HWND outputField;

extern HWND inputDDown;
extern HWND outputDDown;

extern HWND loginPage;

extern HWND hUsername;
extern HWND hPassword;


extern enum UNIT_TYPE inputType, outputType;

extern int tokens;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDCHANGE:
                    printf("heh");
                    DisplayTemperature();
                    break;

                case IDINPUT:
                    inputType = SendMessage(inputDDown, CB_GETCURSEL, 0, 0);
                    break;

                case IDOUTPUT:
                    outputType = SendMessage(outputDDown, CB_GETCURSEL, 0, 0);
                    break;

                case IDLOGIN:
                    loginPage = CreateWindow(
                        "LoginWindowClass",
                        "Login", 
                        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                        CW_USEDEFAULT, CW_USEDEFAULT, 300, 150, 
                        NULL, 
                        NULL, 
                        NULL, 
                        NULL
                    );
                    break;
            }
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

}

LRESULT CALLBACK LoginProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_CREATE: 
        {
            // Create username edit control
            hUsername = CreateWindowEx(
                WS_EX_CLIENTEDGE, 
                "EDIT", 
                "",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
                10, 10, 200, 20,
                hwnd, 
                NULL, 
                NULL, 
                NULL
            );

            // Create password edit control
            hPassword = CreateWindowEx(
                WS_EX_CLIENTEDGE, 
                "EDIT", 
                "",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_PASSWORD,
                10, 40, 200, 20,
                hwnd, 
                NULL, 
                NULL, 
                NULL
            );

            // Create register button
            CreateWindow(
                "BUTTON", 
                "Login",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                10, 70, 100, 30,
                hwnd, 
                (HMENU)1, 
                NULL, 
                NULL
            );

            CreateWindow(
                "BUTTON", 
                "Register",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                110, 70, 100, 30,
                hwnd, 
                (HMENU)2, 
                NULL, 
                NULL
            );
            break;
        }
        break;

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case 1:
                    printf("Login");
                    break;
                case 2:
                    printf("Register");
                    break;
            }
        break;
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{

    FILE *token = fopen("token.txt", "r");
    fscanf(token, "%d", &tokens);
    fclose(token);

    WindowsSetup(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

    MSG msg = {};
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    token = fopen("token.txt", "w");
    fprintf(token, "%d", tokens);
    fclose(token);

    return 0;
}

#pragma once
#include <windows.h>
#define IDINPUT 0
#define IDOUTPUT 1
#define IDCHANGE 2
#define IDLOGIN 3
#define IDCONFIRMLOGIN 4
#define IDREGISTER 5


void DisplayTemperature();
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LoginProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void AddDropUnits(HWND dropdown, int IO);
void WindowsSetup(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
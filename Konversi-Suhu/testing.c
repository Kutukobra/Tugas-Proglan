#include <windows.h>

// Global variables for login window
HWND hUsernameEdit;
HWND hPasswordEdit;

// Function prototypes
LRESULT CALLBACK LoginWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Window procedure callback function
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            // Create a button for login
            CreateWindow("BUTTON", "Login",
                         WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                         10, 10, 100, 30,
                         hwnd, (HMENU)1, NULL, NULL);
            break;
        }
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case 1: // Login button clicked
                    // Create the login window
                    CreateWindowEx(0, "LoginWindowClass", "Login", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                   CW_USEDEFAULT, CW_USEDEFAULT, 300, 150, NULL, NULL, NULL, NULL);
                    break;
            }
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

// Window procedure callback function for the login window
LRESULT CALLBACK LoginWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            // Create username edit control
            hUsernameEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",
                                           WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
                                           10, 10, 200, 20,
                                           hwnd, NULL, NULL, NULL);

            // Create password edit control
            hPasswordEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",
                                           WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_PASSWORD,
                                           10, 40, 200, 20,
                                           hwnd, NULL, NULL, NULL);

            // Create register button
            CreateWindow("BUTTON", "Register",
                         WS_TABSTOP | WS_VISIBLE | WS_CHILD,
                         10, 70, 100, 30,
                         hwnd, (HMENU)2, NULL, NULL);
            break;
        }
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case 2: // Register button clicked
                    MessageBox(hwnd, "Register button clicked!", "Message", MB_OK | MB_ICONINFORMATION);
                    break;
            }
            break;
        }
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

// Entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Register the main window class
    const char CLASS_NAME[] = "MainWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Register the login window class
    const char LOGIN_CLASS_NAME[] = "LoginWindowClass";

    WNDCLASS loginWc = {};
    loginWc.lpfnWndProc = LoginWindowProc;
    loginWc.hInstance = hInstance;
    loginWc.lpszClassName = LOGIN_CLASS_NAME;

    RegisterClass(&loginWc);

    // Create the main window
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles
        CLASS_NAME,                     // Window class
        "Main Window",                  // Window text
        WS_OVERLAPPEDWINDOW,            // Window style
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, // Size and position
        NULL,                           // Parent window
        NULL,                           // Menu
        hInstance,                      // Instance handle
        NULL                            // Additional application data
    );

    if (hwnd == NULL) {
        return 0;
    }

    // Display the main window
    ShowWindow(hwnd, nCmdShow);

    // Run the message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

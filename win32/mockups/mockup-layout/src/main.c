#ifndef UNICODE
#define UNICODE
#endif

#include "layout.h"

#include <windows.h>

LRESULT CALLBACK wnd_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR pCmdLine, int nCmdShow)
{
    // Create and register window class
    WNDCLASS      wc           = {};
    const wchar_t class_name[] = L"window";

    wc.lpfnWndProc   = wnd_proc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = class_name;

    RegisterClass(&wc);

    // Create window
    HWND main_window = CreateWindowEx(
        0, class_name, L"Title", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, 500, 500, NULL, NULL, hInstance, NULL);
    if (main_window == NULL)
    {
        return 0;
    }

    HWND button1 = CreateWindowEx(WS_EX_TRANSPARENT, L"button", L"text",
                                  WS_CHILD | WS_VISIBLE, 0, 0, 100, 100,
                                  main_window, NULL, hInstance, NULL);

    HWND edit1 =
        CreateWindowEx(WS_EX_TRANSPARENT, L"edit", L"text",
                       WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 150, 150, 100,
                       100, main_window, NULL, hInstance, NULL);

    ShowWindow(main_window, nCmdShow);

    MSG msg = {};

    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK wnd_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
    switch (umsg)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
        }
            return 0;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC         hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
            EndPaint(hwnd, &ps);
        }
            return 0;
    }
    return DefWindowProc(hwnd, umsg, wparam, lparam);
}
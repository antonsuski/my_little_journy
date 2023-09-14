#ifndef UNICODE
#define UNICODE
#endif

#include "file_system_wrapper.h"
#include "init_console.h"
#include "treeview.h"

#include <Windows.h>
#include <stdio.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE h_instance, HINSTANCE h_prev_instance,
                    PWSTR p_cmd_line, int n_cmd_show)
{
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = h_instance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(0,          // Optional window styles.
                               CLASS_NAME, // Window class
                               L"Learn to Program Windows", // Window text
                               WS_OVERLAPPEDWINDOW,         // Window style

                               // Size and position
                               300, 300, CW_USEDEFAULT, CW_USEDEFAULT,

                               NULL,       // Parent window
                               NULL,       // Menu
                               h_instance, // Instance handle
                               NULL        // Additional application data
    );

    CreateATreeView(hwnd, h_instance);

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, n_cmd_show);
    init_console();
    char** tmp_str      = NULL;
    size_t tmp_str_size = 0;
    if (!get_directory_content(tmp_str, &tmp_str_size, PATH_TO_EXAMPLES_CLEAR))
    {
        return 1;
    }

    // for (size_t i = 0; i < tmp_str_size; i++)
    // {
    //     printf("[%d]: %s\n", i, tmp_str[i]);
    // }

    // Run the message loop.
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;

    FreeConsole();
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC         hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.

            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint(hwnd, &ps);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
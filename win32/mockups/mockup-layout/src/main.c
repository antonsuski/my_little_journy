
#include <Windows.h>

#include <stdio.h>

LRESULT CALLBACK wnd_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

int WINAPI wWinMain(HINSTANCE hinstance, HINSTANCE h_prev_instance, PWSTR cmd_line, int cmd_show)
{
    // Create and register window class
    WNDCLASS wc  = {};
    const wchar_t class_name[] = L"window";

    wc.lpfnWndProc = wnd_proc;
    wc.hInstance = hinstance;
    wc.lpszClassName = class_name;

    RegisterClass(&wc);

    // Create window
    HWND main_window = CreateWindowEx(0, class_name,L"Title", WS_OVERLAPPED, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hinstance,NULL);
    if (main_window == NULL)
    {
        return 0;
    }

    ShowWindow(main_window, cmd_show);

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
    return 0;
}
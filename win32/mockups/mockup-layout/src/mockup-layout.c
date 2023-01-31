#ifndef UNICODE
#define UNICODE
#endif

#include "layout.h"

#include <windows.h>

static layout_mesh_t mesh;
static WNDPROC origin_btn_proc = NULL;
LRESULT CALLBACK wnd_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
LRESULT CALLBACK btn_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

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
        CW_USEDEFAULT, 315, 338, NULL, NULL, hInstance, NULL);
    if (main_window == NULL)
    {
        return 0;
    }
    // Create mesh
    mesh.mesh_format.x   = 2;
    mesh.mesh_format.y   = 1;
    mesh.layout_type     = HORIZONTAL;
    mesh.mesh_position.x = 50;
    mesh.mesh_position.y = 50;
    mesh.mesh_size.x     = 300;
    mesh.mesh_size.y     = 100;
    create_layout_mesh(&mesh);
    calculate_layout(&mesh);

    HWND button1 = CreateWindowEx(WS_EX_TRANSPARENT, L"BUTTON", L"text",
                                  WS_CHILD | WS_VISIBLE, 0, 0, 100, 100,
                                  main_window, NULL, hInstance, NULL);
    // HWND button2 = CreateWindowEx(WS_EX_TRANSPARENT, L"button", L"text",
    //                               WS_CHILD | WS_VISIBLE, 0, 100, 100, 100,
    //                               main_window, NULL, hInstance, NULL);
    // HWND button3 = CreateWindowEx(WS_EX_TRANSPARENT, L"button", L"text",
    //                               WS_CHILD | WS_VISIBLE, 0, 200, 100, 100,
    //                               main_window, NULL, hInstance, NULL);
    add_control_into_mesh(&mesh, button1);
    origin_btn_proc = (WNDPROC)SetWindowLongPtr(button1, GWLP_WNDPROC, (LONG_PTR)btn_proc);
    // HWND button4 = CreateWindowEx(WS_EX_TRANSPARENT, L"button", L"text",
    //                               WS_CHILD | WS_VISIBLE, 100, 0, 100, 100,
    //                               main_window, NULL, hInstance, NULL);
    // add_control_into_mesh(&mesh, button4);
    // SetWindowLongPtr(button4, GWLP_WNDPROC, (LONG_PTR)btn_proc);
    // HWND button5 = CreateWindowEx(WS_EX_TRANSPARENT, L"button", L"text",
    //                               WS_CHILD | WS_VISIBLE, 100, 100, 100, 100,
    //                               main_window, NULL, hInstance, NULL);
    // HWND button6 = CreateWindowEx(WS_EX_TRANSPARENT, L"button", L"text",
    //                               WS_CHILD | WS_VISIBLE, 100, 200, 100, 100,
    //                               main_window, NULL, hInstance, NULL);
    // HWND button7 = CreateWindowEx(WS_EX_TRANSPARENT, L"button", L"text",
    //                               WS_CHILD | WS_VISIBLE, 200, 0, 100, 100,
    //                               main_window, NULL, hInstance, NULL);
    // HWND button8 = CreateWindowEx(WS_EX_TRANSPARENT, L"button", L"text",
    //                               WS_CHILD | WS_VISIBLE, 200, 100, 100, 100,
    //                               main_window, NULL, hInstance, NULL);
    // HWND button9 = CreateWindowEx(WS_EX_TRANSPARENT, L"button", L"text",
    //                               WS_CHILD | WS_VISIBLE, 200, 200, 100, 100,
    //                               main_window, NULL, hInstance, NULL);

    ShowWindow(main_window, nCmdShow);

    MSG msg = {};

    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    delete_layout_mesh(&mesh);
    return 0;
}

LRESULT CALLBACK wnd_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
    switch (umsg)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC         hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
            EndPaint(hwnd, &ps);
            return 0;
        }
    }
    return DefWindowProc(hwnd, umsg, wparam, lparam);
}

LRESULT CALLBACK btn_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
    // switch (umsg)
    // {
    //     // case WM_CREATE:
    //     // {
    //     //     MessageBox(NULL, L"on create", L"kkew", MB_OK);
    //     //     layout_element_t* elem = get_element(&mesh, hwnd);
    //     //     if (elem == NULL)
    //     //     {
    //     //         MessageBox(NULL, L"can't get elem", L"kkew", MB_OK);
    //     //         return 0;
    //     //     }
    //     //     SetWindowPos(hwnd, NULL, elem->layout_position.x, elem->layout_position.y, elem->layout_size.x, elem->layout_size.y, SWP_NOZORDER | SWP_NOACTIVATE);
    //     //     return 0;
    //     // }
    //     // case WM_DESTROY:
    //     // {
    //     //     PostQuitMessage(0);
    //     //     return 0;
    //     // }
    //     // case WM_PAINT:
    //     // {
    //     //     PAINTSTRUCT ps;
    //     //     HDC         hdc = BeginPaint(hwnd, &ps);
    //     //     FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
    //     //     EndPaint(hwnd, &ps);
    //     //     return 0;
    //     // }
    // }
    // return CallWindowProc((WNDPROC)origin_btn_proc, hwnd,umsg, wparam, lparam);
    return DefWindowProc(hwnd, umsg, wparam, lparam);
}

// #include "layout.h"
// #include <stdio.h>

// int main()
// {
//     layout_mesh_t mesh;
//     mesh.mesh_format.x   = 3;
//     mesh.mesh_format.y   = 1;
//     mesh.layout_type     = HORIZONTAL;
//     mesh.mesh_position.x = 55;
//     mesh.mesh_position.y = 99;
//     mesh.mesh_size.x     = 300;
//     mesh.mesh_size.y     = 100;
//     create_layout_mesh(&mesh);
//     calculate_layout(&mesh);
//     print_mesh(&mesh);
//     delete_layout_mesh(&mesh);
//     return 0;
// }
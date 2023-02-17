#ifndef UNICODE
#define UNICODE
#endif

#include "layout.h"

#include <windows.h>

//statics
static layout_mesh_t mesh;
static WNDPROC origin_btn_proc = NULL;
//buffer
WCHAR buffer[1024] = {0};
//proc
LRESULT CALLBACK wnd_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
LRESULT CALLBACK btn_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lparam);

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
        CW_USEDEFAULT, 315, 500, NULL, NULL, hInstance, NULL);
    if (main_window == NULL)
    {
        return 0;
    }
    // Create mesh
    mesh.format.x   = 3;
    mesh.format.y   = 3;
    mesh.layout_type     = GRID;
    mesh.position.x = 50;
    mesh.position.y = 50;
    mesh.size.x     = 200;
    mesh.size.y     = 200;
    create_layout_mesh(&mesh);
    calculate_layout(&mesh);

    const wchar_t wbc_name[] = L"BUTTON";
    HWND button1 = CreateWindow(wbc_name, L"text",
                                  WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 0, 0, 100, 100,
                                  main_window, NULL, hInstance, NULL);
    add_control_into_mesh(&mesh, button1);
    origin_btn_proc = (WNDPROC)SetWindowLongPtr(button1, GWLP_WNDPROC, (LONG_PTR)btn_proc);

    HWND button2 = CreateWindowEx(WS_EX_TRANSPARENT, L"button", L"text",
                                  WS_CHILD | WS_VISIBLE, 0, 100, 100, 100,
                                  main_window, NULL, hInstance, NULL);
    add_control_into_mesh(&mesh, button2);
    origin_btn_proc = (WNDPROC)SetWindowLongPtr(button2, GWLP_WNDPROC, (LONG_PTR)btn_proc);

    HWND button3 = CreateWindowEx(WS_EX_TRANSPARENT, L"button", L"text",
                                  WS_CHILD | WS_VISIBLE, 0, 200, 100, 100,
                                  main_window, NULL, hInstance, NULL);
    add_control_into_mesh(&mesh, button3);
    origin_btn_proc = (WNDPROC)SetWindowLongPtr(button3, GWLP_WNDPROC, (LONG_PTR)btn_proc);

    HWND button4 = CreateWindowEx(WS_EX_TRANSPARENT, L"button", L"text",
                                  WS_CHILD | WS_VISIBLE, 100, 0, 100, 100,
                                  main_window, NULL, hInstance, NULL);
    add_control_into_mesh(&mesh, button4);
    origin_btn_proc = (WNDPROC)SetWindowLongPtr(button4, GWLP_WNDPROC, (LONG_PTR)btn_proc);

    HWND button5 = CreateWindowEx(WS_EX_TRANSPARENT, L"button", L"text",
                                  WS_CHILD | WS_VISIBLE, 100, 100, 100, 100,
                                  main_window, NULL, hInstance, NULL);
    add_control_into_mesh(&mesh, button5);
    origin_btn_proc = (WNDPROC)SetWindowLongPtr(button5, GWLP_WNDPROC, (LONG_PTR)btn_proc);

    HWND button6 = CreateWindowEx(WS_EX_TRANSPARENT, L"button", L"text",
                                  WS_CHILD | WS_VISIBLE, 100, 200, 100, 100,
                                  main_window, NULL, hInstance, NULL);
    add_control_into_mesh(&mesh, button6);
    origin_btn_proc = (WNDPROC)SetWindowLongPtr(button6, GWLP_WNDPROC, (LONG_PTR)btn_proc);

    HWND button7 = CreateWindowEx(WS_EX_TRANSPARENT, L"button", L"text",
                                  WS_CHILD | WS_VISIBLE, 200, 0, 100, 100,
                                  main_window, NULL, hInstance, NULL);
    add_control_into_mesh(&mesh, button7);
    origin_btn_proc = (WNDPROC)SetWindowLongPtr(button7, GWLP_WNDPROC, (LONG_PTR)btn_proc);

    HWND button8 = CreateWindowEx(WS_EX_TRANSPARENT, L"button", L"text",
                                  WS_CHILD | WS_VISIBLE, 200, 100, 100, 100,
                                  main_window, NULL, hInstance, NULL);
    add_control_into_mesh(&mesh, button8);
    origin_btn_proc = (WNDPROC)SetWindowLongPtr(button8, GWLP_WNDPROC, (LONG_PTR)btn_proc);

    HWND button9 = CreateWindowEx(WS_EX_TRANSPARENT, L"button", L"text",
                                  WS_CHILD | WS_VISIBLE, 200, 200, 100, 100,
                                  main_window, NULL, hInstance, NULL);
    add_control_into_mesh(&mesh, button9);
    origin_btn_proc = (WNDPROC)SetWindowLongPtr(button9, GWLP_WNDPROC, (LONG_PTR)btn_proc);

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
        case WM_SIZING:
        {
            RECT rect;
            GetWindowRect(hwnd, &rect);
            mesh.size.x = abs(rect.right - rect.left) - (2 * mesh.position.x);
            mesh.size.y = abs(rect.bottom - rect.top) - (2 * mesh.position.y);
            calculate_layout(&mesh);
            EnumChildWindows(hwnd, EnumChildProc, lparam);
            // RedrawWindow(hwnd, NULL, NULL, RDW_UPDATENOW | RDW_ALLCHILDREN);
            return 0;
        }
    }
    return DefWindowProc(hwnd, umsg, wparam, lparam);
}

// #define TRACK_MOUSE_EVENT \
// do {\
// TRACKMOUSEEVENT __tme = { sizeof(__tme) };\
// __tme.dwFlags = TME_LEAVE;\
// __tme.hwndTrack = hwnd;\
// TrackMouseEvent(&__tme); } while (0)
LRESULT CALLBACK btn_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
    static int is_mousehovered = 0;
    static HWND mousehovered_window_handle = NULL;
    switch (umsg)
        {
        // case WM_MOUSEMOVE:
        // {
        //     TRACK_MOUSE_EVENT;
        //     if (mousehovered_window_handle != hwnd);
        //     {
        //         mousehovered_window_handle = hwnd;
        //     }
        // } break;
        // case WM_MOUSELEAVE:
        // {
        //     mousehovered_window_handle = NULL;
        //     RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
        // } break;
        case WM_LBUTTONDOWN:
        {
            // if(mousehovered_window_handle == hwnd)
            // {
                layout_element_t* elem = get_element(&mesh, hwnd);
                if (elem == NULL)
                {
                    MessageBox(NULL, L"can't get elem", L"kkew", MB_OK);
                    return 0;
                }
            RECT rect;
            GetWindowRect(hwnd, &rect);
                wsprintf(buffer, L"pos:%d:%d\nsiz:%d:%d\nmes:%d,%d\nmes_s:%d:%d\nwnd_s:%d\nwnd_p:%d:%d\n",elem->layout_position.x, elem->layout_position.y,
                                    elem->layout_size.x, elem->layout_size.y, elem->layout_position_in_mesh.x,elem->layout_position_in_mesh.y,
                                    mesh.size.x, mesh.size.y, abs(rect.right - rect.left), rect.left, rect.top);
                SetWindowPos(hwnd, NULL, elem->layout_position.x, elem->layout_position.y, elem->wnd_desc.window_size.x, elem->wnd_desc.window_size.y, SWP_SHOWWINDOW | SWP_NOACTIVATE);
                MessageBox(hwnd, buffer, L"laout elem", MB_OK);
            // }
        } break;
        case WM_SIZE:
        {
            layout_element_t* elem = get_element(&mesh, hwnd);
            if (elem == NULL)
            {
                MessageBox(NULL, L"can't get elem", L"kkew", MB_OK);
                return 0;
            }
            SetWindowPos(hwnd, NULL, elem->layout_position.x, elem->layout_position.y, elem->wnd_desc.window_size.x, elem->wnd_desc.window_size.y, SWP_SHOWWINDOW | SWP_NOACTIVATE);
            RedrawWindow(hwnd, NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE);
        } break;
    }
    return CallWindowProc((WNDPROC)origin_btn_proc, hwnd, umsg, wparam, lparam);
}

BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lparam)
{
    SendMessage(hwnd, WM_SIZE, 0, lparam);
    return TRUE;
}
//mesh example
// #include "layout.h"
// #include <stdio.h>

// int main()
// {
//     layout_mesh_t mesh;
//     mesh.format.x   = 3;
//     mesh.format.y   = 1;
//     mesh.layout_type     = HORIZONTAL;
//     mesh.position.x = 55;
//     mesh.position.y = 99;
//     mesh.size.x     = 300;
//     mesh.size.y     = 100;
//     create_layout_mesh(&mesh);
//     calculate_layout(&mesh);
//     print_mesh(&mesh);
//     delete_layout_mesh(&mesh);
//     return 0;
// }
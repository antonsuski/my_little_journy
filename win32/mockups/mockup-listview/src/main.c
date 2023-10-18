#include "file_system_wrapper.h"

#include <Windows.h>
#include <commctrl.h>

#include <stdlib.h>
#include <stdio.h>

LRESULT CALLBACK win_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR pCmdLine, int nCmdShow)
{
    int col, row;
    wchar_t*** buffer = pars_csv_file("3.csv", &col, &row);

    if (buffer)
    {
        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
            {
                printf("%ls,", buffer[i][j]);
            }
            printf("\n");
        }
    }

    WNDCLASS wc = {};
    const wchar_t class_name[] = L"window";

    wc.lpfnWndProc = win_proc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "window";

    RegisterClass(&wc);
    HWND main_window = CreateWindowExW(0, class_name, L"lv", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, NULL, NULL, hInstance, NULL);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0,0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK win_proc(HWND hwnd, UINT msg, WPARAM w_param,
                                    LPARAM l_param) {
    NMLVDISPINFO* list_view_disp_info;

    switch (msg)
    {
        case WM_NOTIFY:
        {
            switch (((LPNMHDR)l_param)->code)
            {
                case LVN_GETDISPINFO:
                {
                    // list_view_disp_info = (NMLVDISPINFO*)l_param;
                    // list_view_disp_info->item.pszText =
                    //     g_list_view_storage[list_view_disp_info->item.iItem]
                    //     // [list_view_disp_info->item.iSubItem];
                }
                break;
            }
        }
        break;
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        break;
    }

    return DefWindowProc(hwnd, msg, w_param, l_param);
    // return CallWindowProc((WNDPROC)_origin_window_wndproc, hwnd, msg, w_param,
    //                       l_param);
}
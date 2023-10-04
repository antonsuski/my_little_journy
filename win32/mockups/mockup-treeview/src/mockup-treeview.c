#ifndef UNICODE
#define UNICODE
#endif

#include "file_system_wrapper.h"
#include "init_console.h"
#include "treeview.h"

#include <Windows.h>
#include <stdio.h>

#define PATH_TO_EXAMPLES_CLEAR "D:\\vm_shared_folder\\er-dock\\logs"
#define PATH_TO_LOG_DIRECTORIES "C:\\Users\\Public\\Documents"

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

    init_console();
    HWND tree_view = create_treeview_list(hwnd, h_instance, 0, 0, 300, 300);

    if (hwnd == NULL)
    {
        return 0;
    }

    HTREEITEM hti;

    char** tmp_str      = NULL;
    size_t tmp_str_size = 0;
    if (!(tmp_str = get_directory_content( &tmp_str_size, PATH_TO_LOG_DIRECTORIES)))
    {
        return 1;
    }

    heading_t* headings = (heading_t*)malloc(tmp_str_size * sizeof(heading_t));

    for (size_t i = 0; i < tmp_str_size; i++)
    {
        mbstowcs(headings[i].tchar_heading, tmp_str[i], MAX_HEADING_LEN);
        if (i % 2 == 0)
        {
            headings[i].heading_level = 1;
        }
        else
        {
            headings[i].heading_level = 2;
        }

        printf("[%zu]: %s\n", i, tmp_str[i]);
    }

    if (tmp_str)
    {
        for (size_t i = 0; i < tmp_str_size; i++)
        {
            free(tmp_str[i]);
        }
        free(tmp_str);
    }

    for (int i = 0; i < tmp_str_size; i++)
    {
        // Add the item to the tree-view control.
        hti = add_item_to_treeview(tree_view, &headings[i]);

        if (hti == NULL)
        {
            return 1;
        }
    }

    ShowWindow(hwnd, n_cmd_show);

    // Run the message loop.
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    free(headings);
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
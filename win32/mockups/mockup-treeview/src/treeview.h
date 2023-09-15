// #pragma once

#ifndef kekw
#define kekw

#ifndef UNICODE
#define UNICODE
#endif

#include "file_system_wrapper.h"

#include <Windows.h>
#include <winuser.h>

#include <CommCtrl.h>

#define CX_BITMAP 15
#define CY_BITMAP 15
#define NUM_BITMAPS 3
#define MAX_HEADING_LEN 256

typedef struct
{
    TCHAR tchar_Heading[MAX_HEADING_LEN];
    int   heading_level;
} heading_t;

HWND CreateATreeView(HWND hwndParent, HINSTANCE hInst);

HTREEITEM AddItemToTree(HWND hwndTV, LPTSTR lpszItem, int nLevel);

BOOL InitTreeViewImageLists(HWND hwndTV, HINSTANCE hInst);
BOOL InitTreeViewItems(HWND hwndTV);

#endif
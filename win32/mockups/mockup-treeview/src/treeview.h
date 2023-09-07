// #pragma once

#ifndef kekw
#define kekw

#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>
#include <CommCtrl.h>
#include <winuser.h>

#define CX_BITMAP 10
#define CY_BITMAP 10
#define NUM_BITMAPS 3
#define MAX_HEADING_LEN 256

typedef struct
{
    TCHAR tchar_Heading[MAX_HEADING_LEN];
    int   heading_level;
} Heading;

static Heading g_rgDocHeadings[3] = {{'A', 1},{'B', 2},{'C', 2}};

HWND CreateATreeView(HWND hwndParent, HINSTANCE hInst);

HTREEITEM AddItemToTree(HWND hwndTV, LPTSTR lpszItem, int nLevel);

BOOL InitTreeViewImageLists(HWND hwndTV, HINSTANCE hInst);
BOOL InitTreeViewItems(HWND hwndTV);

#endif
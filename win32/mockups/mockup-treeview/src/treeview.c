#include "resources.h"
#include "treeview.h"

#include <stdio.h>

static int        g_document;
static int        g_closed;
static int        g_open;
static int        g_headings_count;
static heading_t* g_headings;

HWND CreateATreeView(HWND hwndParent, HINSTANCE hInst)
{
    RECT rcClient; // dimensions of client area
    HWND hwndTV;   // handle to tree-view control

    INITCOMMONCONTROLSEX icex;
    icex.dwICC = ICC_TREEVIEW_CLASSES;
    // Ensure that the common control DLL is loaded.
    InitCommonControlsEx(&icex);

    // Get the dimensions of the parent window's client area, and create
    // the tree-view control.
    GetClientRect(hwndParent, &rcClient);
    hwndTV = CreateWindowEx(0, WC_TREEVIEW, TEXT("Tree View"),
                            WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES, 0,
                            0, rcClient.right, rcClient.bottom, hwndParent,
                            NULL, hInst, NULL);

    // Initialize the image list, and add items to the control.
    // InitTreeViewImageLists and InitTreeViewItems are application-
    // defined functions, shown later.

    if (!InitTreeViewImageLists(hwndTV, hInst))
    {
        MessageBox(NULL, L"can't init vew image list", L"image", MB_OK);
    }

    if (!InitTreeViewItems(hwndTV))
    {
        MessageBox(NULL, L"can't init vew items", L"items", MB_OK);
    }

    // if (!InitTreeViewImageLists(hwndTV, hInst) || !InitTreeViewItems(hwndTV))
    // {
    //     DestroyWindow(hwndTV);
    //     return FALSE;
    // }
    // InitTreeViewItems(hwndTV);
    return hwndTV;
}

BOOL InitTreeViewImageLists(HWND hwndTV, HINSTANCE hInst)
{
    HIMAGELIST himl; // handle to image list
    HBITMAP    hbmp; // handle to bitmap

    // Create the image list.
    if ((himl = ImageList_Create(CX_BITMAP, CY_BITMAP, FALSE, NUM_BITMAPS,
                                 0)) == NULL)
        return FALSE;

    // Add the open file, closed file, and document bitmaps.
    hbmp = LoadBitmapW(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
    if (hbmp == NULL)
    {
        wchar_t error_msg[1024];
        DWORD   error = GetLastError();
        FormatMessage(
            FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL,
            error, 0, error_msg, sizeof(error_msg) / sizeof(wchar_t), NULL);
        MessageBox(NULL, error_msg, L"kekw", MB_ICONERROR);
    }
    g_open = ImageList_Add(himl, hbmp, (HBITMAP)NULL);
    // DeleteObject(hbmp);

    // hbmp      = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP));
    g_closed = ImageList_Add(himl, hbmp, (HBITMAP)NULL);
    // DeleteObject(hbmp);

    // hbmp        = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP));
    g_document = ImageList_Add(himl, hbmp, (HBITMAP)NULL);
    DeleteObject(hbmp);

    // Fail if not all of the images were added.
    int res_count = ImageList_GetImageCount(himl);
    if (res_count < NUM_BITMAPS)
    {
        return FALSE;
    }

    // Associate the image list with the tree-view control.
    TreeView_SetImageList(hwndTV, himl, TVSIL_NORMAL);

    return TRUE;
}

HTREEITEM AddItemToTree(HWND hwndTV, LPTSTR lpszItem, int nLevel)
{
    TVITEM           tvi;
    TVINSERTSTRUCT   tvins;
    static HTREEITEM hPrev         = (HTREEITEM)TVI_FIRST;
    static HTREEITEM hPrevRootItem = NULL;
    static HTREEITEM hPrevLev2Item = NULL;
    HTREEITEM        hti;

    tvi.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    // Set the text of the item.
    tvi.pszText    = lpszItem;
    tvi.cchTextMax = sizeof(tvi.pszText) / sizeof(tvi.pszText[0]);

    // Assume the item is not a parent item, so give it a
    // document image.
    tvi.iImage         = g_document;
    tvi.iSelectedImage = g_document;

    // Save the heading level in the item's application-defined
    // data area.
    tvi.lParam         = (LPARAM)nLevel;
    tvins.item         = tvi;
    tvins.hInsertAfter = hPrev;
    // Set the parent item based on the specified level.
    if (nLevel == 1)
        tvins.hParent = TVI_ROOT;
    else if (nLevel == 2)
        tvins.hParent = hPrevRootItem;
    else
        tvins.hParent = hPrevLev2Item;

    // Add the item to the tree-view control.
    hPrev = (HTREEITEM)SendMessage(hwndTV, TVM_INSERTITEM, 0,
                                   (LPARAM)(LPTVINSERTSTRUCT)&tvins);

    if (hPrev == NULL)
        return NULL;

    // Save the handle to the item.
    if (nLevel == 1)
        hPrevRootItem = hPrev;
    else if (nLevel == 2)
        hPrevLev2Item = hPrev;

    // The new item is a child item. Give the parent item a
    // closed folder bitmap to indicate it now has child items.
    if (nLevel > 1)
    {
        hti                = TreeView_GetParent(hwndTV, hPrev);
        tvi.mask           = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
        tvi.hItem          = hti;
        tvi.iImage         = g_closed;
        tvi.iSelectedImage = g_closed;
        TreeView_SetItem(hwndTV, &tvi);
    }

    return hPrev;
}

// Extracts heading text and heading levels from a global
// array and passes them to a function that adds them as
// parent and child items to a tree-view control.
// Returns TRUE if successful, or FALSE otherwise.
// hwndTV - handle to the tree-view control.

BOOL InitTreeViewItems(HWND hwndTV)
{
    HTREEITEM hti;

    char** tmp_str      = NULL;
    size_t tmp_str_size = 0;
    if (!(tmp_str = get_directory_content(
              &tmp_str_size, "D:\\vm_shared_folder\\er-dock\\logs")))
    {
        return 1;
    }

    g_headings = (heading_t*)malloc(tmp_str_size * sizeof(heading_t));

    for (size_t i = 0; i < tmp_str_size; i++)
    {
        size_t converted_chars = 0;
        mbstowcs(g_headings[i].tchar_Heading, tmp_str[i], MAX_HEADING_LEN);
        g_headings[i].heading_level = 1;
        printf("[%d]: %s\n", i, tmp_str[i]);
    }

    if (tmp_str)
    {
        for (size_t i = 0; i < tmp_str_size; i++)
        {
            free(tmp_str[i]);
        }
        free(tmp_str);
    }

    // g_rgDocHeadings is an application-defined global array of
    // the following structures:
    //     typedef struct
    //       {
    //         TCHAR tchHeading[MAX_HEADING_LEN];
    //         int tchLevel;
    //     } Heading;
    for (int i = 0; i < tmp_str_size; i++)
    {
        // Add the item to the tree-view control.
        hti = AddItemToTree(hwndTV, g_headings[i].tchar_Heading,
                            g_headings[i].heading_level);

        if (hti == NULL)
            return FALSE;
    }

    return TRUE;
}

#include "resources.h"
#include "treeview.h"

#include <stdio.h>

static int g_document;
static int g_closed;
static int g_open;

static BOOL init_tree_view_image_lists(HWND hwnd, HINSTANCE h_inst)
{
    HIMAGELIST himl; // handle to image list
    HBITMAP    hbmp; // handle to bitmap

    // Create the image list.
    if ((himl = ImageList_Create(CX_BITMAP, CY_BITMAP, FALSE, NUM_BITMAPS,
                                 0)) == NULL)
        return FALSE;

    // Add the open file, closed file, and document bitmaps.
    hbmp = LoadBitmapW(h_inst, MAKEINTRESOURCE(IDB_BITMAP1));
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
    TreeView_SetImageList(hwnd, himl, TVSIL_NORMAL);
    return TRUE;
}

HWND create_treeview_list(HWND hwnd_parent, HINSTANCE h_inst, int pos_x,
                          int pos_y, int size_x, int size_y)
{
    RECT rcClient; // dimensions of client area
    HWND hwndTV;   // handle to tree-view control

    INITCOMMONCONTROLSEX icex;
    icex.dwICC = ICC_TREEVIEW_CLASSES;
    // Ensure that the common control DLL is loaded.
    InitCommonControlsEx(&icex);

    // Get the dimensions of the parent window's client area, and create
    // the tree-view control.
    GetClientRect(hwnd_parent, &rcClient);
    hwndTV = CreateWindowEx(0, WC_TREEVIEW, TEXT("Tree View"),
                            WS_VISIBLE | WS_CHILD | TVS_LINESATROOT |
                                TVS_FULLROWSELECT | TVS_HASBUTTONS,
                            pos_x, pos_y, size_x, size_y, hwnd_parent, NULL,
                            h_inst, NULL);
    if (!init_tree_view_image_lists(hwndTV, h_inst))
    {
        return NULL;
    }

    return hwndTV;
}

HTREEITEM add_item_to_treeview(HWND hwnd, heading_t* heading)
{
    TVITEM           tvi;
    TVINSERTSTRUCT   tvins;
    static HTREEITEM hPrev         = (HTREEITEM)TVI_FIRST;
    static HTREEITEM hPrevRootItem = NULL;
    static HTREEITEM hPrevLev2Item = NULL;
    HTREEITEM        hti;

    tvi.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;

    // Set the text of the item.
    tvi.pszText = heading->tchar_heading;
    // wcscpy(tvi.pszText, heading->tchar_heading);
    tvi.cchTextMax = wcslen(tvi.pszText);

    // Assume the item is not a parent item, so give it a
    // document image.
    tvi.iImage         = g_document;
    tvi.iSelectedImage = g_document;

    // Save the heading level in the item's application-defined
    // data area.
    tvi.lParam         = (LPARAM)heading->heading_level;
    tvins.item         = tvi;
    tvins.hInsertAfter = hPrev;
    // Set the parent item based on the specified level.
    if (heading->heading_level == 1)
        tvins.hParent = TVI_ROOT;
    else if (heading->heading_level == 2)
        tvins.hParent = hPrevRootItem;
    else
        tvins.hParent = hPrevLev2Item;

    // Add the item to the tree-view control.
    hPrev = (HTREEITEM)SendMessage(hwnd, TVM_INSERTITEM, 0,
                                   (LPARAM)(LPTVINSERTSTRUCT)&tvins);

    if (hPrev == NULL)
        return NULL;

    // Save the handle to the item.
    if (heading->heading_level == 1)
        hPrevRootItem = hPrev;
    else if (heading->heading_level == 2)
        hPrevLev2Item = hPrev;

    // The new item is a child item. Give the parent item a
    // closed folder bitmap to indicate it now has child items.
    if (heading->heading_level > 1)
    {
        hti                = TreeView_GetParent(hwnd, hPrev);
        tvi.mask           = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
        tvi.hItem          = hti;
        tvi.iImage         = g_closed;
        tvi.iSelectedImage = g_closed;
        TreeView_SetItem(hwnd, &tvi);
    }

    return hPrev;
}

#include "treeview.h"
#include "resources.h"

static int g_nDocument;

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
    // if (!InitTreeViewImageLists(hwndTV) || !InitTreeViewItems(hwndTV))
    // {
    //     DestroyWindow(hwndTV);
    //     return FALSE;
    // }
    InitTreeViewItems(hwndTV);
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

    // // Add the open file, closed file, and document bitmaps.
    // hbmp    = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_OPEN_FILE));
    // g_nOpen = ImageList_Add(himl, hbmp, (HBITMAP)NULL);
    // DeleteObject(hbmp);

    // hbmp      = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_CLOSED_FILE));
    // g_nClosed = ImageList_Add(himl, hbmp, (HBITMAP)NULL);
    // DeleteObject(hbmp);

    hbmp        = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
    g_nDocument = ImageList_Add(himl, hbmp, (HBITMAP)NULL);
    DeleteObject(hbmp);

    // Fail if not all of the images were added.
    if (ImageList_GetImageCount(himl) < 1)
        return FALSE;

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
    tvi.iImage = g_nDocument;
    tvi.iSelectedImage = g_nDocument;

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
        hti       = TreeView_GetParent(hwndTV, hPrev);
        tvi.mask  = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
        tvi.hItem = hti;
        // tvi.iImage = g_nClosed;
        // tvi.iSelectedImage = g_nClosed;
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

    // g_rgDocHeadings is an application-defined global array of
    // the following structures:
    //     typedef struct
    //       {
    //         TCHAR tchHeading[MAX_HEADING_LEN];
    //         int tchLevel;
    //     } Heading;
    for (int i = 0; i < ARRAYSIZE(g_rgDocHeadings); i++)
    {
        // Add the item to the tree-view control.
        hti = AddItemToTree(hwndTV, g_rgDocHeadings[i].tchHeading,
                            g_rgDocHeadings[i].tchLevel);

        if (hti == NULL)
            return FALSE;
    }

    return TRUE;
}

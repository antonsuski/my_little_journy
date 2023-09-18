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

#define CX_BITMAP 15        /*< Width of bmp icon*/
#define CY_BITMAP 15        /*< Height of bmp icon*/
#define NUM_BITMAPS 3       /*< Number of icons*/
#define MAX_HEADING_LEN 256 /*< Max heading lenght*/

/**
 * @brief Structure for adding items into tree view
 *
 */
typedef struct
{
    TCHAR tchar_heading[MAX_HEADING_LEN]; /*< Name of item*/
    int   heading_level;                  /*< Item level at treeview*/
} heading_t;

/**
 * @brief Create a treeview list window
 *
 * @param[in] hwnd_parent Parent window descriptor
 * @param[in] h_inst Program instance
 * @param[in] pos_x x position
 * @param[in] pos_y y postion
 * @param[in] size_x x size
 * @param[in] size_y y size
 * @return HWND tree veiw descriptor if success, return NULL if failure
 */
HWND create_treeview_list(HWND hwnd_parent, HINSTANCE h_inst, int pos_x,
                          int pos_y, int size_x, int size_y);

/**
 * @brief Adds new item into treeview
 *
 * @param[in] hwnd Parent treeview window descriptor
 * @param[in] heading Structure with item heading and level in treeview
 * @return HTREEITEM return treeview item is success, return NULL if not
 */
HTREEITEM add_item_to_treeview(HWND hwnd, heading_t* heading);

#endif

/**
 * @file layout.h
 * @project EasyRail Dock
 * @author Anton Suskiy (Anton.SUSKIY.ext@hitachirail.com)
 * @date 2023-02-14
 */

// Header guard
#pragma once

/** @includes ---------------------------------------------------------------**/
#include "windows.h"

/** @typedefs ---------------------------------------------------------------**/
/**
 * @brief Types of layout.
 *
 */
typedef enum
{
    HORIZONTAL = 1, /*< Lays windows in a horizontal row */
    VERTICAL   = 2, /*< Lays windows in a vertical column */
    GRID       = 3, /*< Lays windows in a two-dimensional grid */
} layout_t;

/**
 * @brief Window descriptor for storing window attributes
 *
 */
typedef struct
{
    HWND  hwnd;             /*< Window descriptor */
    POINT window_size;      /*< Window size */
    POINT window_position;  /*< Window position */
} window_descriptro_t;

/**
 * @brief For storing layout element attributes
 *
 */
typedef struct
{
    BOOL                in_use;                     /*< Detect that the element are used or not */
    POINT               layout_size;                /*< Size of element in mesh */
    POINT               layout_position;            /*< Position of top left corner accordin with mesh size and element size in user space*/
    POINT               layout_position_in_mesh;    /*< Index position of element in mesh */
    window_descriptro_t wnd_desc;                   /*< Window descriptor */
    void*               mesh;                       /*< Pointer to nested mesh*/
} layout_element_t;

/**
 * @brief For storing mesh with elements
 *
 */
typedef struct
{
    layout_element_t** elements;    /*< Array of elements */
    layout_t           layout_type; /*< Type of layout */
    POINT              position;    /*< Position of mesh according user space in main window */
    POINT              size;        /*< Size of mesh */
    POINT              format;      /*< Format of mesh for HORIZONTAL (n:1) for VERTICAL (1:m) for GRID (n:m)
                                        where n - count of elements in row, m - count of elements in column*/
} layout_mesh_t;

/** @prototypes -------------------------------------------------------------**/

/**
 * @brief Creates a layout mesh object, allocates memory in heap. Mark all in_use fields with FALSE
 *
 * @param[in, out] mesh Pointer to mesh
 */
void create_layout_mesh(layout_mesh_t* mesh);

/**
 * @brief Deletes mesh and freeing allocated memory
 *
 * @param[in, out] mesh Pointer to mesh
 */
void delete_layout_mesh(layout_mesh_t* mesh);

/**
 * @brief Calculates elements size, position according mesh size
 *
 * @param[in, out] mesh Pointer to mesh
 */
void calculate_layout(layout_mesh_t* mesh);

/**
 * @brief Set up winodws positions inside mesh and redraw it.
 *
 * @param[in, out] mesh Pointer to mesh
 */
void redraw_mesh(layout_mesh_t* mesh);

/**
 * @brief Adds control/window in mesh
 *
 * @param[in, out] mesh Pointer to mesh
 * @param[in] hwnd Window descriptor
 * @return BOOL Returns TRUE if addition is seccessfull, returns FALSE if failed
 */
BOOL add_control_into_mesh(layout_mesh_t* mesh, HWND hwnd);

/**
 * @brief The function adds child mesh (nested) inside parent mesh
 *
 * @param[in, out] parent_mesh Pointer to parent mesh
 * @param[in] child_mesh Pointer to child mesh which you want to nest
 * @return BOOL Return TRUE if addition is seccessfull, reutrn FALSE if failed
 */
BOOL add_child_mesh_into_mesh(layout_mesh_t* parent_mesh, layout_mesh_t* child_mesh);

/**
 * @brief Get the element object. Finds using a window/controller handle
 *
 * @param mesh Pointer to mesh
 * @param hwnd Window desriptor
 * @return layout_element_t* Returns pointer to layout_element_t if success, return NULL if failed
 */
layout_element_t* get_element(layout_mesh_t* mesh, HWND hwnd);

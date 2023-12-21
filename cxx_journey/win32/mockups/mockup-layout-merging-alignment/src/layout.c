/** @includes ---------------------------------------------------------------**/
#include "layout.h"

#include <windows.h>

#include <memory.h>
#include <stdio.h>

/** @definitions -------------------------------------------------------------**/
void create_layout_mesh(layout_mesh_t* mesh)
{
    // For vertical column count is 1
    if (mesh->layout_type == VERTICAL)
    {
        mesh->format.x = 1;
    }
    // For horizontal row count is 1
    if (mesh->layout_type == HORIZONTAL)
    {
        mesh->format.y = 1;
    }
    // Memory allocation
    mesh->elements = (layout_element_t**)malloc(mesh->format.x *
                                                sizeof(layout_element_t*));
    for (size_t i = 0; i < mesh->format.x; i++)
    {
        mesh->elements[i] = (layout_element_t*)malloc(mesh->format.y *
                                                      sizeof(layout_element_t));
        for (size_t j = 0; j < mesh->format.y; j++)
        {
            // Fill in in_use field with FALSE
            mesh->elements[i][j].in_use = FALSE;
        }
    }
    return;
}

void delete_layout_mesh(layout_mesh_t* mesh)
{
    // Memory freeing
    for (size_t i = 0; i < mesh->format.x; i++)
    {
        free(mesh->elements[i]);
    }
    free(mesh->elements);
    mesh->elements = NULL;
    return;
}

void calculate_layout(layout_mesh_t* mesh)
{
    // Element size calculation
    POINT element_size;
    element_size.x = mesh->size.x / mesh->format.x;
    element_size.y = mesh->size.y / mesh->format.y;

    // Go through whole mesh and fill in data
    for (size_t i = 0; i < mesh->format.x; i++)
    {
        for (size_t j = 0; j < mesh->format.y; j++)
        {
            mesh->elements[i][j].layout_size.x = element_size.x;
            mesh->elements[i][j].layout_size.y = element_size.y;
            mesh->elements[i][j].layout_position.x =
                i * element_size.x + mesh->position.x;
            mesh->elements[i][j].layout_position.y =
                j * element_size.y + mesh->position.y;
            mesh->elements[i][j].layout_position_in_mesh.x = i;
            mesh->elements[i][j].layout_position_in_mesh.y = j;

            if (mesh->elements[i][j].mesh != NULL)
            {
                layout_mesh_t* child_mesh = ((layout_mesh_t*)mesh->elements[i][j].mesh);
                child_mesh->size = mesh->elements[i][j].layout_size;
                child_mesh->position = mesh->elements[i][j].layout_position;
                calculate_layout(child_mesh);
            }
        }
    }

    // Since division of two integer numbers there are an error accamulate
    // Do corrections for last element in mesh if an error presetn
    int division_error_x = mesh->size.x - (element_size.x * mesh->format.x);
    int division_error_y = mesh->size.y - (element_size.y * mesh->format.y);

    if (division_error_x > 0)
    {
        mesh->elements[mesh->format.x - 1][mesh->format.y - 1].layout_size.x += division_error_x;
    }

    if (division_error_y)
    {
        mesh->elements[mesh->format.x - 1][mesh->format.y - 1].layout_size.y += division_error_y;
    }
    return;
}

BOOL add_control_into_mesh(layout_mesh_t* mesh, HWND hwnd)
{
    // Goes through whole mesh
    for (size_t i = 0; i < mesh->format.x; i++)
    {
        for (size_t j = 0; j < mesh->format.y; j++)
        {
            // Finds layout elemnt which not used
            if (mesh->elements[i][j].in_use == FALSE)
            {
                RECT rect;
                GetWindowRect(hwnd, &rect);
                MapWindowPoints(HWND_DESKTOP, GetParent(hwnd), (LPPOINT)&rect,
                                2);
                mesh->elements[i][j].wnd_desc.window_position.x = rect.left;
                mesh->elements[i][j].wnd_desc.window_position.y = rect.top;
                mesh->elements[i][j].wnd_desc.window_size.x =
                    abs(rect.right - rect.left);
                mesh->elements[i][j].wnd_desc.window_size.y =
                    abs(rect.bottom - rect.top);
                mesh->elements[i][j].wnd_desc.hwnd = hwnd;
                mesh->elements[i][j].in_use        = TRUE;
                // Sets pointer to mesh for window/controller which will be added
                SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)mesh);
                return TRUE;
            }
        }
    }
    // Returns FALSE if no free element was found
    return FALSE;
}

layout_element_t* get_element(layout_mesh_t* mesh, HWND hwnd)
{
    // Goes through whole mesh
    for (size_t i = 0; i < mesh->format.x; i++)
    {
        for (size_t j = 0; j < mesh->format.y; j++)
        {
            // Finds element by window/controller handle
            if (mesh->elements[i][j].wnd_desc.hwnd == hwnd)
            {
                return &mesh->elements[i][j];
            }
        }
    }
    // If no matches return NULL
    return NULL;
}

void redraw_mesh(layout_mesh_t* mesh)
{
    // Go through whole mesh
    for (size_t i = 0; i < mesh->format.x; i++)
    {
        for (size_t j = 0; j < mesh->format.y; j++)
        {
            // Set up position for all windows
            // After SetWindowPos call the Windows OS automatically redraw window
            SetWindowPos(mesh->elements[i][j].wnd_desc.hwnd, NULL,
                         mesh->elements[i][j].layout_position.x,
                         mesh->elements[i][j].layout_position.y,
                         mesh->elements[i][j].layout_size.x,
                         mesh->elements[i][j].layout_size.y,
                         SWP_NOACTIVATE);

            // Redraw nested mesh
            if (mesh->elements[i][j].mesh != NULL)
            {
                redraw_mesh((layout_mesh_t*)mesh->elements[i][j].mesh);
            }
        }
    }
}

BOOL add_child_mesh_into_mesh(layout_mesh_t* parent_mesh,
                              layout_mesh_t* child_mesh)
{
    // Go through whole mesh
    for (size_t i = 0; i < parent_mesh->format.x; i++)
    {
        for (size_t j = 0; j < parent_mesh->format.y; j++)
        {
            // Set data if mesh is not in use
            if (parent_mesh->elements[i][j].in_use == FALSE)
            {
                parent_mesh->elements[i][j].mesh   = (void*)child_mesh;
                parent_mesh->elements[i][j].in_use = TRUE;
                return TRUE;
            }
        }
    }
    return FALSE;
}

void print_mesh(layout_mesh_t* mesh)
{
    printf("mesh pos: %d:%d\nmesh size: %d:%d\nmesh format: %d:%d\n",
           mesh->position.x, mesh->position.y, mesh->size.x, mesh->size.y,
           mesh->format.x, mesh->format.y);

    for (size_t i = 0; i < mesh->format.x; i++)
    {
        printf("layout size: %d:%d \nlayout position: %d:%d \nlayout position "
               "in mesh: %d:%d \n",
               mesh->elements[i][0].layout_size.x,
               mesh->elements[i][0].layout_size.y,
               mesh->elements[i][0].layout_position.x,
               mesh->elements[i][0].layout_position.y,
               mesh->elements[i][0].layout_position_in_mesh.x,
               mesh->elements[i][0].layout_position_in_mesh.y);
    }
}
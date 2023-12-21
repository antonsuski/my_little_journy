#include "layout.h"

#include <windows.h>

#include <memory.h>
#include <stdio.h>

void swap(unsigned int* a, unsigned int* b)
{
    unsigned int temp = *a;
    *a = *b;
    *b = temp;
}

void create_layout_mesh(layout_mesh_t* mesh)
{
    // if ((mesh->layout_type == HORIZONTAL && (mesh->format.y > mesh->format.x))
    //     || (mesh->layout_type == VERTICAL && (mesh->format.x > mesh->format.y)))
    // {
    //     swap(mesh->format.x, mesh->format.y);
    // }

    if (mesh->format.x == 0 || mesh->layout_type == VERTICAL)
    {
        mesh->format.x = 1;
        // inseart warning log;
    }
    if (mesh->format.y == 0 || mesh->layout_type == HORIZONTAL)
    {
        mesh->format.y = 1;
        // inseart warning log;
    }
    mesh->elements = (layout_element_t**)malloc(mesh->format.x *
                                                sizeof(layout_element_t*));
    for (size_t i = 0; i < mesh->format.x; i++)
    {
        mesh->elements[i] = (layout_element_t*)malloc(mesh->format.y *
                                                      sizeof(layout_element_t));
        for (size_t j = 0; j < mesh->format.y; j++)
        {
            mesh->elements[i][j].in_use = FALSE;
        }
    }

    return;
}

void delete_layout_mesh(layout_mesh_t* mesh)
{
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
    POINT element_size;
    element_size.x = mesh->size.x / mesh->format.x;
    element_size.y = mesh->size.y / mesh->format.y;

    switch (mesh->layout_type)
    {
        case HORIZONTAL:
        {
            for (size_t i = 0; i < mesh->format.x; i++)
            {
                mesh->elements[i][0].layout_size.x = element_size.x;
                mesh->elements[i][0].layout_size.y = element_size.y;
                mesh->elements[i][0].layout_position.x =
                    i * element_size.x + mesh->position.x;
                mesh->elements[i][0].layout_position.y =
                    0 + mesh->position.y;
                mesh->elements[i][0].layout_position_in_mesh.x = i;
                mesh->elements[i][0].layout_position_in_mesh.y = 0;
            }
        }
        break;
        case VERTICAL:
        {
            for (size_t i = 0; i < mesh->format.y; i++)
            {
                mesh->elements[0][i].layout_size.x = element_size.x;
                mesh->elements[0][i].layout_size.y = element_size.y;
                mesh->elements[0][i].layout_position.x =
                    mesh->position.x;
                mesh->elements[0][i].layout_position.y =
                    i * element_size.y + mesh->position.y;
                mesh->elements[0][i].layout_position_in_mesh.x = 0;
                mesh->elements[0][i].layout_position_in_mesh.y = i;
            }
        }
        break;
        case GRID:
        {
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
                }
            }
        }
        break;
        default:
            return;
    }
    return;
}

void print_mesh(layout_mesh_t* mesh)
{
    printf("mesh pos: %d:%d\nmesh size: %d:%d\nmesh format: %d:%d\n",
           mesh->position.x, mesh->position.y, mesh->size.x,
           mesh->size.y, mesh->format.x, mesh->format.y);

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

BOOL add_control_into_mesh(layout_mesh_t* mesh, HWND hwnd)
{
    for (size_t i = 0; i < mesh->format.x; i++)
    {
        for (size_t j = 0; j < mesh->format.y; j++)
        {
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
                SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)mesh);
                return TRUE;
            }
        }
    }
    return FALSE;
}

layout_element_t* get_element(layout_mesh_t* mesh, HWND hwnd)
{
    for (size_t i = 0; i < mesh->format.x; i++)
    {
        for (size_t j = 0; j < mesh->format.y; j++)
        {
            if (mesh->elements[i][j].wnd_desc.hwnd == hwnd)
            {
                return &mesh->elements[i][j];
            }
        }
    }
    return NULL;
}
#include "layout.h"

#include "windows.h"

#include "memory.h"

void create_layout_mesh(layout_mesh_t* mesh, POINT* mesh_format)
{
    if (mesh->mesh_format.x == 0)
    {
        mesh->mesh_format.x = 1;
        // inseart warning log;
    }
    if (mesh->mesh_format.y == 0)
    {
        mesh->mesh_format.y = 1;
        // inseart warning log;
    }
    mesh->elements = (layout_element_t**)malloc(mesh->mesh_format.x *
                                                sizeof(layout_element_t*));
    for (size_t i = 0; i < mesh->mesh_format.x; i++)
    {
        mesh->elements[i] = (layout_element_t*)malloc(mesh_format->y *
                                                      sizeof(layout_element_t));
    }

    return;
}

void delete_layout_mesh(layout_mesh_t* mesh)
{
    for (size_t i = 0; i < mesh->mesh_format.x; i++)
    {
        free(mesh->elements[i]);
    }
    free(mesh->elements);
    mesh->elements = NULL;
    return;
}

void calculate_layout(layout_mesh_t* mesh)
{
    switch (mesh->layout_type)
    {
        case HORIZONTAL:
        {
            POINT element_size;
            element_size.x = mesh->mesh_size.x / mesh->mesh_format.x;
            element_size.y = mesh->mesh_size.y;
            for (size_t i = 0; i < mesh->mesh_format.x; i++)
            {
                mesh->elements[0][i].layout_size.x     = element_size.x;
                mesh->elements[0][i].layout_size.y     = element_size.y;
                mesh->elements[0][i].layout_position.x = i * element_size.x;
                mesh->elements[0][i].layout_position.y = 0;
                mesh->elements[0][i].layout_position_in_mesh.x = i;
                mesh->elements[0][i].layout_position_in_mesh.y = 0;
            }

            return;
        }
        break;

        default:
            return;
    }
    return;
}

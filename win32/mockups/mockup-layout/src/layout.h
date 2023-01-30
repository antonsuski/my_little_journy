#include "windows.h"

typedef enum
{
    HORIZONTAL = 1,
    VERTICAL   = 2,
    GRID       = 3,
} layout_t;

typedef struct
{
    HWND* hwnd;
    POINT window_size;
    POINT window_position;
} window_descriptro_t;

typedef struct
{
    POINT               layout_size;
    POINT               layout_position;
    POINT               layout_position_in_mesh;
    window_descriptro_t wnd_desc;
} layout_element_t;

typedef struct
{
    layout_element_t** elements;
    layout_t           layout_type;
    POINT              mesh_position;
    POINT              mesh_size;
    POINT              mesh_format;
} layout_mesh_t;

void             create_layout_mesh(layout_mesh_t* mesh);
void             delete_layout_mesh(layout_mesh_t* mesh);
void             calculate_layout(layout_mesh_t* mesh);
layout_element_t calculate_layout_element(layout_control_t);
#include "windows.h"

typedef enum
{
    HORIZONTAL = 1,
    VERTICAL   = 2,
    GRID       = 3,
} layout_t;

typedef struct
{
    HWND  hwnd;
    POINT window_size;
    POINT window_position;
} window_descriptro_t;

typedef struct
{
    BOOL                in_use;
    POINT               layout_size;
    POINT               layout_position;
    POINT               layout_position_in_mesh;
    window_descriptro_t wnd_desc;
} layout_element_t;

typedef struct
{
    layout_element_t** elements;
    layout_t           layout_type;
    POINT              position;
    POINT              size;
    POINT              format;
} layout_mesh_t;

void create_layout_mesh(layout_mesh_t* mesh);
void delete_layout_mesh(layout_mesh_t* mesh);
void calculate_layout(layout_mesh_t* mesh);
void print_mesh(layout_mesh_t* mesh);

BOOL add_control_into_mesh(layout_mesh_t* mesh, HWND hwnd);

layout_element_t* get_element(layout_mesh_t* mesh, HWND hwnd);
#include "windows.h"

typedef enum
{
    HORIZONTAL = 1,
    VERTICAL   = 2,
    GRID       = 3,
} layout_t;

typedef struct
{
    HWND*    hwnd;
    POINT    window_size;
    POINT    window_position;
    POINT    layout_size;
    POINT    layout_position;
    layout_t layout_type;
} window_descriptro_t;

typedef struct
{
    window_descriptro_t wind_desc;
} layout_control_t;

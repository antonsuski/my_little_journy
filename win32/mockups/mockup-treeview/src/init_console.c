#include "init_console.h"

#include <stdio.h>

void init_console()
{
    if (AttachConsole(ATTACH_PARENT_PROCESS))
    {
        FILE *fpstdin = stdin, *fpstdout = stdout, *fpstderr = stderr;
        freopen_s(&fpstdin, "CONIN$", "r", stdin);
        freopen_s(&fpstdout, "CONOUT$", "w", stdout);
        freopen_s(&fpstderr, "CONOUT$", "w", stderr);
    }
    printf("Hello, world!\n");
}
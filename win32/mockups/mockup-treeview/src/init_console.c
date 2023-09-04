#include "init_console.h"

void init_console()
{
    if (AttachConsole(ATTACH_PARENT_PROCESS))
    {
        FILE *fpstdin = stdin, *fpstdout = stdout, *fpstderr = stderr;
        freopen_s(&fpstdin, "CONIN$", "r", stdin);
        freopen_s(&fpstdout, "CONOUT$", "w", stdout);
        freopen_s(&fpstderr, "CONOUT$", "w", stderr);
    }
}
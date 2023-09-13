#include "file_system_wrapper.h"

#include <stdio.h>
#include <string.h>
#include <tchar.h>
#include <windows.h>

#define MAX_PATH_SIZE 1024
#define PATH_TO_EXAMPLES "D:\\vm_shared_folder\\er-dock\\logs\\*\0"

char** get_directory_content(const char* path_to_directory)
{
    printf("%s, args: %s\n", __func__, path_to_directory);

    DWORD           result;
    TCHAR           buffer[MAX_PATH_SIZE];
    HANDLE          file;
    WIN32_FIND_DATA finded_data;
    LARGE_INTEGER   file_size;

    result = GetCurrentDirectory(MAX_PATH_SIZE, buffer);
    strcat(buffer, TEXT("\\*"));
    printf("current dir:%s\n", buffer);

    file = FindFirstFile(PATH_TO_EXAMPLES, &finded_data);
    if (file == INVALID_HANDLE_VALUE)
    {
        printf("can't find first file");
    }

    do
    {
        if (finded_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            _tprintf(TEXT(" %s <DIR>\n"), finded_data.cFileName);
        }
        else
        {

            file_size.LowPart  = finded_data.nFileSizeLow;
            file_size.HighPart = finded_data.nFileSizeHigh;
            _tprintf(TEXT(" %s   %ld bytes\n"), finded_data.cFileName,
                     file_size.QuadPart);
        }

    } while (FindNextFile(file, &finded_data) != 0);

    FindClose(&finded_data);
    return NULL;
}
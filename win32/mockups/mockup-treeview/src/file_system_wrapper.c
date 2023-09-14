#include "file_system_wrapper.h"

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

#define MAX_PATH_SIZE 1024
#define PATH_TO_EXAMPLES "D:\\vm_shared_folder\\er-dock\\logs\\*\0"

bool get_directory_content(char** contents_buffer, size_t* buffer_size,
                           const char* path_to_directory)
{
    HANDLE          file;
    WIN32_FIND_DATA finded_data;
    LARGE_INTEGER   file_size;
    char            path[MAX_PATH] = { 0 };

    strcpy(path, path_to_directory);
    strcat(path, "\\*");

    // Count all files in directory
    file = FindFirstFile(path, &finded_data);

    if (file == INVALID_HANDLE_VALUE)
    {
        printf("can't find first file");
    }

    do
    {
        if (!(finded_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            (*buffer_size)++;
        }
    } while (FindNextFile(file, &finded_data) != 0);

    FindClose(&finded_data);

    // Allocate memory for directrory content list
    contents_buffer = (char**)malloc((*buffer_size) * sizeof(char*));

    if (!contents_buffer)
    {
        printf("Can't allocate memory for char**");
        return false;
    }

    for (size_t i = 0; i < *buffer_size; i++)
    {
        contents_buffer[i] = (char*)malloc(sizeof(char[MAX_PATH_SIZE]));
        if (!contents_buffer[i])
        {
            printf("Can't allocate memory for char*");
            return false;
        }
    }

    // Write contetn
    file = FindFirstFile(PATH_TO_EXAMPLES, &finded_data);

    if (file == INVALID_HANDLE_VALUE)
    {
        printf("can't find first file");
    }

    do
    {
        if (!(finded_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            for (size_t i = 0; i < *buffer_size; i++)
            {
                strncpy(contents_buffer[i], finded_data.cFileName,
                        MAX_PATH_SIZE);
            }
        }
    } while (FindNextFile(file, &finded_data) != 0);

    FindClose(&finded_data);

    for (size_t i = 0; i < *buffer_size; i++)
    {
        printf("[%d]: %s\n", i, contents_buffer[i]);
    }

    return true;
}

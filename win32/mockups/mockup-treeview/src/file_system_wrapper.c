#include "file_system_wrapper.h"

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** get_directory_content(size_t* buffer_size, const char* path_to_directory)
{
    HANDLE          file;
    WIN32_FIND_DATA finded_data;
    char            path[MAX_PATH] = { 0 };
    char**          contents_buffer;

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
        return NULL;
    }

    for (size_t i = 0; i < *buffer_size; i++)
    {
        contents_buffer[i] = (char*)malloc(sizeof(char[MAX_PATH]));
        if (!contents_buffer[i])
        {
            printf("Can't allocate memory for char*");
            free(contents_buffer);
            return NULL;
        }
    }

    // Write contetn
    file = FindFirstFile(path, &finded_data);

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
                strncpy(contents_buffer[i], finded_data.cFileName, MAX_PATH);
            }
        }
    } while (FindNextFile(file, &finded_data) != 0);

    FindClose(&finded_data);

    return contents_buffer;
}

#include "file_system_wrapper.h"

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int count_char(const wchar_t* src, const wchar_t match)
{
    int res = 0;
    int count = wcslen(src);

    for (size_t i = 0; i < count; i++)
    {
        if (src[i] == match)
        {
            res++;
        }
    }

    return res;
}

// wchar_t** get_directory_content(size_t* buffer_size, const char* path_to_directory)
// {
//     HANDLE          file;
//     WIN32_FIND_DATA finded_data;
//     char            path[MAX_PATH] = { 0 };
//     wchar_t**          contents_buffer;
//     WCHAR search_path[MAX_PATH] = { 0 };

//     strcpy(path, path_to_directory);
//     strcat(path, "*.csv");
//     MultiByteToWideChar(CP_UTF8, 0, path, MAX_PATH, search_path, MAX_PATH);

//     // Count all files in directory 
//     file = FindFirstFileEx(search_path, FindExInfoStandard, &finded_data, FindExSearchNameMatch, NULL, 0);

//     if (file == INVALID_HANDLE_VALUE)
//     {
//         printf("Can't find first file, first time\n");
//     }

//     do
//     {
//         if (!(finded_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
//         {
//             (*buffer_size)++;
//         }
//     } while (FindNextFile(file, &finded_data) != 0);

//     FindClose(&finded_data);

//     // Allocate memory for directrory content list
//     contents_buffer = (wchar_t**)malloc((*buffer_size) * sizeof(wchar_t*));

//     if (!contents_buffer)
//     {
//         printf("Can't allocate memory for char**\n");
//         return NULL;
//     }

//     for (size_t i = 0; i < *buffer_size; i++)
//     {
//         contents_buffer[i] = (wchar_t*)malloc(sizeof(wchar_t[MAX_PATH]));
//         if (!contents_buffer[i])
//         {
//             printf("Can't allocate memory for char*\n");
//             free(contents_buffer);
//             return NULL;
//         }
//     }

//     // Write contetn
//     file = FindFirstFileEx(search_path, FindExInfoStandard, &finded_data, FindExSearchNameMatch, NULL, 0);

//     if (file == INVALID_HANDLE_VALUE)
//     {
//         printf("Can't find first file\n");
//     }

//     size_t i = 0;
//     do
//     {
//         if (!(finded_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
//             wcsncpy(contents_buffer[i++], finded_data.cFileName, MAX_PATH);
//             printf("[%zu]: %ls\n", i, finded_data.cFileName);
//         }
//     } while (FindNextFile(file, &finded_data) != 0);

//     FindClose(&finded_data);

//     return contents_buffer;
// }

wchar_t*** pars_csv_file(const char* path, int* columns_num, int* rows_num) {
    // Open file
    FILE* file = NULL;
    wchar_t*** columns = NULL;
    wchar_t buffer[4096] = {0};
    wchar_t* start = buffer;

    // Get row count from file
    *rows_num = count_file_lines(path);

    errno_t err = fopen_s(&file, path, "r");
    if (err) {
        return NULL;
    }

    // Parse
    int is_memmory_allocated = 0;
    size_t row_idx = 0;

    while (fgetws(buffer, 4096, file)) {
        // Memmory allocation
        if (!is_memmory_allocated) {
            *columns_num = count_char(buffer, L',');
            columns = (wchar_t***)calloc(*rows_num, sizeof(wchar_t**));

            for (size_t i = 0; i < *rows_num; i++) {
              columns[i] = (wchar_t**)calloc(*columns_num, sizeof(wchar_t*));
              for (size_t j = 0; j < *columns_num; j++) {
                columns[i][j] = (wchar_t*)calloc(MAX_PATH, sizeof(wchar_t));
              }
            }

            is_memmory_allocated = 1;
        }

        size_t col_idx = 0;
        start = buffer;
        wchar_t* ptr_terminator = NULL;
        while (ptr_terminator = wcswcs(start, L",")) {
            *ptr_terminator = '\0';
            wcsncpy(columns[row_idx][col_idx], start, MAX_PATH);
            start = ptr_terminator + 1;
            col_idx++;
        }
        row_idx++;
    }

    // Clean
    fclose(file);
    return columns;
}

int count_file_lines(const char* path)
{
    int res = 0;

    // Open file
    FILE* file = NULL;
    errno_t err = fopen_s(&file, path, "r");
    if (err)
    {
        printf("Can't open file %s", path);
        return res;
    }
    char c = 0;
    // Count lines
    do
    {
        if (feof(file))
            break;
        c = fgetc(file);
        if (c == '\n')
            res++;


    } while (1);

    fclose(file);
    return res;
}

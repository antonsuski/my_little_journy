#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_PATH 260

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

static int count_lines(char* path)
{
    int res = 0;

    FILE* file;
    file = fopen(path, "r");
    if (!file)
    {
        printf("Can't open file %s", path);
        return 0;
    }

    int lines_count = 0;
    do
    {
        char c = fgetc(file);
        if (c == '\n')
        {
            lines_count++;
        }

        if (feof(file))
        {
            break;
        }
    } while (1);

    fclose(file);
    return res = lines_count;
}

static wchar_t*** pars_csv_file(const char* path, int* columns_num,
                         int* rows_num)
{
    // Open file
    FILE* file = NULL;
    wchar_t*** columns = NULL;
    wchar_t buffer[4096] = { 0 };
    wchar_t* start = buffer;

    // Get row count from file
    *rows_num = count_lines(path);

    errno_t err = fopen_s(&file, path, "r");
    if(err)
    {
        return NULL;
    }

    // Parse
    int is_memmory_allocated = 0;
    size_t row_idx = 0;

    while (fgetws(buffer, 4096, file)) {
        // Memmory allocation
        if (!is_memmory_allocated)
        {
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

    fclose(file);
    return columns;
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Usage: gfl <path_to_file>\n");
        return 1;
    }

    // printf("lines in file: %d\n", count_lines(argv[1]));

    // total count of comma: 7
    // wchar_t test_str[100] = L"test, string, for, finding, count, of, commas, inside\0";
    // printf("count of ,:%d\n", count_char(test_str, L','));

    int col, row;
    char*** buffer = pars_csv_file(argv[1], &col, &row);

    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < col; j++)
        {
            printf("%ls ", buffer[i][j]);
        }
        printf("\n");
    }
    return 0;
}

/**
 * @file file_system_wrapper.h
 * @author anton (you@domain.com)
 * @brief
 * @date 2023-09-19
 */

// Header guard
#ifndef FILE_SYSTEM_WRAPPER_H
#define FILE_SYSTEM_WRAPPER_H

#include <stddef.h>
#include <wchar.h>

// /**
//  * @brief Get the directory content string list.
//  *
//  * @param[in, out] buffer_size Return number of strings.
//  * @param[in] path_to_directory Path to target directory.
//  * @return char** Returns NULL if function is faild else returns pointer to
//  * allocated strings array. Be sure to free memory after using obtained
//  * data;
//  */
// wchar_t** get_directory_content(size_t* buffer_size,
//                                 const char* path_to_directory);

/**
 * @brief This function do csv file parsing.
 *
 * @param[in] path Path to csv file.
 * @param[out] columns Pointer to number of parsed columns.
 * @param[out] rows Pointer ot number of parsed rows.
 * @return wchar_t** Return pointer to table of strings, the first row of
 * strings will contain header of table. Return NULL if failure.
 */
wchar_t*** pars_csv_file(const char* path, int* columns_num,
                        int* rows);

/**
 * @brief Provide count of lines in file
 *
 * @param[in] path Path to target file
 * @return int Return count of lines if success or 0 if not
 */
int count_file_lines(const char* path);

#endif  // FILE_SYSTEM_WRAPPER_H

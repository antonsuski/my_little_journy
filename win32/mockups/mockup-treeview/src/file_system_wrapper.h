/**
 * @file file_system_wrapper.h
 * @author your name (you@domain.com)
 * @brief
 * @date 2023-09-15
 */

// Header guard
#ifndef FILE_SYSTEM_WRAPPER_H
#define FILE_SYSTEM_WRAPPER_H

#include <stddef.h>

/**
 * @brief Get the directory content string list.
 *
 * @param[in, out] buffer_size Return number of strings.
 * @param[in] path_to_directory Path to target directory.
 * @return char** Returns NULL if function is faild, returns pointer to strings
 * array if not.
 */
char** get_directory_content(size_t*     buffer_size,
                             const char* path_to_directory);

#endif // FILE_SYSTEM_WRAPPER_H

/**
 * @file file_system_wrapper.h
 * @project EasyRail Dock
 * @author Anton Syski (Anton.SUSKIY.ext@hitachirail.com)
 * @brief This is file define small wrapper for Win32 API file system
 * @date 2023-09-12
 */

// Header guard
#ifndef FILE_SYSTEM_WRAPPER_H
#define FILE_SYSTEM_WRAPPER_H

char** get_directory_content(const char* path_to_directory);
#endif // FILE_SYSTEM_WRAPPER_H

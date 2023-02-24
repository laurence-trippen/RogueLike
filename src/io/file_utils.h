#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdint.h>
#include <stdbool.h>

int32_t io_get_file_line_count(const char* path, bool ignore_empty_lines);

#endif

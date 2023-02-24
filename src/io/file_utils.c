#include "file_utils.h"

#include <stdio.h>
#include <stdbool.h>

int32_t io_get_file_line_count(const char* path, bool ignore_empty_lines)
{
	FILE* file = fopen(path, "r");
	if (file == NULL)
	{
		puts("Error: Couldn't open file to count lines!");
		return -1;
	}

	char single_line[150];

	int32_t line_count = 0;

	while (!feof(file))
	{
		fgets(single_line, 150, file);

		if (ignore_empty_lines == true)
		{
			// If empty line "\n" then skip cycle
			if (*single_line == '\n')
			{
				continue;
			}
		}

		line_count++;
	}

	fclose(file);

	return line_count;
}

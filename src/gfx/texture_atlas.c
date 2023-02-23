#include "texture_atlas.h"

#include <stdio.h>
#include <stdlib.h>


GFX_Texture_Atlas* gfx_load_texture_atlas(const char* path)
{
	FILE* file;
	char* line = NULL;

	size_t len = 0;
	// ssize_t read;


	file = fopen(path, "r");
	if (file == NULL)
	{
		puts("Error: Couldn't open Atlas File!");
		return NULL;
	}

	puts("Successfully opened file");

	fclose(file);
}

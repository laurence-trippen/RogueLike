#include "texture_atlas.h"

// #define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 150
#define ATLAS_PROP_INDEX_TITLE 1
#define ATLAS_PROP_INDEX_X 2
#define ATLAS_PROP_INDEX_Y 3
#define ATLAS_PROP_INDEX_W 4
#define ATLAS_PROP_INDEX_H 5
#define ATLAS_PROP_INDEX_FRAMES 6


GFX_Texture_Atlas* gfx_load_texture_atlas(const char* path)
{
	FILE* file = fopen(path, "r");
	if (file == NULL)
	{
		puts("Error: Couldn't open Atlas File!");
		return NULL;
	}

	puts("Successfully opened file");

	char single_line[MAX_LINE_LENGTH];
	char delimiter[] = " ";

	while (!feof(file))
	{
		fgets(single_line, MAX_LINE_LENGTH, file);

		puts(single_line);

		// Splitting
		char* word_ptr = strtok(single_line, delimiter);
		
		uint8_t word_count = 0;

		GFX_Texture_Atlas_Entry atlas_entry = {
			"Test",
			0, 0, 0, 0,
			0
		};

		while (word_ptr != NULL)
		{
			word_count++;

			switch (word_count)
			{
			case ATLAS_PROP_INDEX_TITLE:
				// TODO: Fix Access Violation
				strcpy(atlas_entry.title, word_ptr);
				break;
			case ATLAS_PROP_INDEX_X:
				atlas_entry.x = atoi(word_ptr);
				break;
			case ATLAS_PROP_INDEX_Y:
				atlas_entry.y = atoi(word_ptr);
				break;
			}
			
			printf("%d\n", word_count);
			printf("'%s'\n", word_ptr);

			word_ptr = strtok(NULL, delimiter);
		}

		printf("Title: %s, X: %d, Y: %d\n", atlas_entry.title, atlas_entry.x, atlas_entry.y);
		puts("-----");
	}

	fclose(file);

	return NULL;
}

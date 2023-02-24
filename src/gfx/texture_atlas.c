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

		// If empty line "\n" then skip cycle
		if (*single_line == '\n')
		{
			continue;
		}
		
		// Splitting
		char* word_ptr = strtok(single_line, delimiter);
		
		uint8_t word_count = 0;

		GFX_Texture_Atlas_Entry* atlas_entry = (GFX_Texture_Atlas_Entry*) malloc(sizeof(GFX_Texture_Atlas_Entry));

		// Check if allocation wasn't successful
		if (atlas_entry == NULL) return NULL;

		// Set Default values for entry
		atlas_entry->x = 0;
		atlas_entry->y = 0;
		atlas_entry->w = 0;
		atlas_entry->h = 0;
		atlas_entry->frames = 0;

		while (word_ptr != NULL)
		{
			word_count++;

			switch (word_count)
			{
			case ATLAS_PROP_INDEX_TITLE:
				// First allocate memory for string
				atlas_entry->title = malloc(sizeof(char) * strlen(word_ptr));

				// Check if allocation wasn't successful
				if (atlas_entry->title == NULL) return NULL;

				// Copy word to struct memory pointer
				strcpy(atlas_entry->title, word_ptr);
				break;
			case ATLAS_PROP_INDEX_X:
				atlas_entry->x = atoi(word_ptr);
				break;
			case ATLAS_PROP_INDEX_Y:
				atlas_entry->y = atoi(word_ptr);
				break;
			case ATLAS_PROP_INDEX_W:
				atlas_entry->w = atoi(word_ptr);
				break;
			case ATLAS_PROP_INDEX_H:
				atlas_entry->h = atoi(word_ptr);
				break;
			case ATLAS_PROP_INDEX_FRAMES:
				atlas_entry->frames = atoi(word_ptr);
				break;
			}
			
			// printf("%d\n", word_count);
			// printf("'%s'\n", word_ptr);

			word_ptr = strtok(NULL, delimiter);
		}

		printf(
			"Title: %s, X: %d, Y: %d, W: %d, H: %d, F: %d\n", 
			atlas_entry->title, 
			atlas_entry->x, 
			atlas_entry->y,
			atlas_entry->w,
			atlas_entry->h,
			atlas_entry->frames
		);

		puts("-----");
	}

	fclose(file);

	return NULL;
}

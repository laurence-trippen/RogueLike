#include "texture_atlas.h"

// #define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../io/file_utils.h"

#define MAX_LINE_LENGTH 150
#define ATLAS_PROP_INDEX_TITLE 1
#define ATLAS_PROP_INDEX_X 2
#define ATLAS_PROP_INDEX_Y 3
#define ATLAS_PROP_INDEX_W 4
#define ATLAS_PROP_INDEX_H 5
#define ATLAS_PROP_INDEX_FRAMES 6


GFX_Texture_Atlas* gfx_load_texture_atlas(const char* path)
{
	int32_t line_count = io_get_file_line_count(path, true);
	printf("Entry count: %d\n", line_count);
	if (line_count < 0)
	{
		return NULL;
	}

	FILE* file = fopen(path, "r");
	if (file == NULL)
	{
		puts("Error: Couldn't open Atlas File!");
		return NULL;
	}

	puts("Successfully opened file");

	// Atlas structure
	GFX_Texture_Atlas* atlas = (GFX_Texture_Atlas*) malloc(sizeof(GFX_Texture_Atlas));
	if (atlas == NULL) return NULL;

	// Initialize atlas
	atlas->length = line_count;
	atlas->entries = (GFX_Texture_Atlas_Entry*) calloc(line_count, sizeof(GFX_Texture_Atlas_Entry));
	if (atlas->entries == NULL) return NULL;

	// Line by line reading with tokenizing
	char single_line[MAX_LINE_LENGTH];
	char delimiter[] = " ";

	uint32_t line_counter = 0;
	while (!feof(file))
	{
		fgets(single_line, MAX_LINE_LENGTH, file);

		// puts(single_line);

		// If empty line "\n" then skip cycle
		if (*single_line == '\n')
		{
			continue;
		}
		
		// Splitting
		char* word_ptr = strtok(single_line, delimiter);
		
		GFX_Texture_Atlas_Entry* atlas_entry = &(atlas->entries[line_counter]);
		line_counter++;

		uint8_t word_count = 0;
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

		/*
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
		*/
	}

	fclose(file);

	return atlas;
}


// Finds entry via ID string compare. This operation is linear and should be better replaced with a Hash-Table.
GFX_Texture_Atlas_Entry* gfx_find_atlas_entry_by_id(GFX_Texture_Atlas* p_atlas, const char* id)
{
	if (p_atlas == NULL) return NULL;

	for (int i = 0; i < p_atlas->length; i++)
	{
		if (*(p_atlas->entries[i].title) == *id)
		{
			return &(p_atlas->entries[i]);
		}
	}

	return NULL;
}


void gfx_debug_print_atlas(GFX_Texture_Atlas* p_atlas)
{
	for (int i = 0; i < p_atlas->length; i++)
	{
		printf("Title: %s\n", p_atlas->entries[i].title);
		printf("X: %d\n", p_atlas->entries[i].x);
		printf("Y: %d\n", p_atlas->entries[i].y);
		printf("W: %d\n", p_atlas->entries[i].w);
		printf("H: %d\n", p_atlas->entries[i].h);
		printf("F: %d\n", p_atlas->entries[i].frames);
		printf("----\n");
	}
}


void gfx_debug_print_atlas_entry(GFX_Texture_Atlas_Entry* p_atlas_entry)
{
	if (p_atlas_entry == NULL) return;

	printf("Title: %s\n", p_atlas_entry->title);
	printf("X: %d\n", p_atlas_entry->x);
	printf("Y: %d\n", p_atlas_entry->y);
	printf("W: %d\n", p_atlas_entry->w);
	printf("H: %d\n", p_atlas_entry->h);
	printf("F: %d\n", p_atlas_entry->frames);
}

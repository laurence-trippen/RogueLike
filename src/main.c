#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_image.h>

#include "gfx/texture_atlas.h"

int main(int argc, char* args[])
{
	// Window
	SDL_Window* window = SDL_CreateWindow("RogueLike", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, NULL);
	if (!window)
	{
		SDL_Log("Could not create a window: %s", SDL_GetError());
		return -1;
	}

	// Renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
		return -1;
	}

	// Load Media
	SDL_Texture* texture = IMG_LoadTexture(renderer, "assets/test.png");
	if (!texture)
	{
		SDL_Log("Could not load texture: %s", SDL_GetError());
		return -1;
	}

	SDL_Rect texture_rect;
	texture_rect.x = 10;		// the x coordinate
	texture_rect.y = 10;		// the y coordinate
	texture_rect.w = 50;	// the width of the texture
	texture_rect.h = 50;	// the height of the texture

	// Should have 161x entries
	GFX_Texture_Atlas* p_atlas = gfx_load_texture_atlas("assets/DungeonTileset/tiles_list_v1.4");
	printf("Atlas Entries: %zu\n", p_atlas->length);

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

	// Game Loop
	bool done = false;
	while (!done)
	{
		// Get the next event
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				done = true;
			}
		}

		// Set the color to cornflower blue and clear
		SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
		SDL_RenderClear(renderer);

		SDL_Rect clip_rect;
		clip_rect.x = 0;
		clip_rect.y = 0;
		clip_rect.w = 10;
		clip_rect.h = 10;

		SDL_RenderCopy(renderer, texture, NULL, &texture_rect);

		// Show the renderer contents
		SDL_RenderPresent(renderer);
	}

	// Cleanup
	// TODO: Free Texture Atlas

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

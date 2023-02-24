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

	// Window Icon
	SDL_Surface* window_icon = IMG_Load("assets/test.png");
	SDL_SetWindowIcon(window, window_icon);

	// Renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
		return -1;
	}

	// Load Media
	SDL_Texture* texture = IMG_LoadTexture(renderer, "assets/DungeonTileset/0x72_DungeonTilesetII_v1.4.png");
	if (!texture)
	{
		SDL_Log("Could not load texture: %s", SDL_GetError());
		return -1;
	}

	SDL_Rect texture_rect;
	texture_rect.x = 50;		// the x coordinate
	texture_rect.y = 50;		// the y coordinate
	texture_rect.w = 20;	// the width of the texture
	texture_rect.h = 60;	// the height of the texture

	// Should have 161x entries
	GFX_Texture_Atlas* p_atlas = gfx_load_texture_atlas("assets/DungeonTileset/tiles_list_v1.4");
	printf("Atlas Entries: %zu\n", p_atlas->length);

	gfx_debug_print_atlas(p_atlas);

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

		int index = 80;

		SDL_Rect clip_rect;
		clip_rect.x = p_atlas->entries[index].x;
		clip_rect.y = p_atlas->entries[index].y;
		clip_rect.w = p_atlas->entries[index].w;
		clip_rect.h = p_atlas->entries[index].h;

		SDL_RenderCopy(renderer, texture, &clip_rect, &texture_rect);

		// Show the renderer contents
		SDL_RenderPresent(renderer);
	}

	// Cleanup
	// TODO: Free Texture Atlas

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

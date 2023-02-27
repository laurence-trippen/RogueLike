#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_image.h>

#include "gfx/texture_atlas.h"
#include "gfx/renderer.h"

#include "game/game.h"
#include "game/game_object.h"

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
	gfx_init_renderer(window);

	// Load Media
	gfx_load_main_atlas_texture("assets/DungeonTileset/0x72_DungeonTilesetII_v1.4.png");

	// Should have 161x entries
	GFX_Texture_Atlas* p_atlas_data = gfx_load_texture_atlas("assets/DungeonTileset/tiles_list_v1.4");
	printf("Atlas Entries: %zu\n", p_atlas_data->length);
	// gfx_debug_print_atlas(p_atlas);

	Game_Object* knife = game_create_gameobject("skull", p_atlas_data);
	knife->transform->x = 50.0f;
	knife->transform->y = 50.0f;
	knife->transform->w *= 3.0f;
	knife->transform->h *= 3.0f;

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

		knife->angle += 0.01;

		// Cornflowerblue like in XNA =)
		gfx_clear(100, 149, 237, 255);

		gfx_render_gameobject(knife);

		gfx_present();
	}

	// Cleanup
	free(knife);
	knife = NULL;

	// TODO: Free Texture Atlas

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

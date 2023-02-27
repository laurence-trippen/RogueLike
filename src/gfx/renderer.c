#include "renderer.h"

void gfx_init_renderer(const SDL_Window* p_window)
{
	g_gpu_renderer = SDL_CreateRenderer(p_window, -1, SDL_RENDERER_ACCELERATED);
	if (!g_gpu_renderer)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
		// return -1;
	}

	g_flip_type = SDL_FLIP_NONE;
}

void gfx_load_main_atlas_texture(const char* p_path)
{
	g_main_atlas_texture = IMG_LoadTexture(g_gpu_renderer, p_path);
	if (!g_main_atlas_texture)
	{
		SDL_Log("Could not load texture: %s", SDL_GetError());
		// return -1;
	}
}


void gfx_render_gameobject(const Game_Object* p_game_object)
{
	static SDL_Rect s_clip_rect, s_tex_rect;

	s_clip_rect.x = p_game_object->p_atlas_entry->x;
	s_clip_rect.y = p_game_object->p_atlas_entry->y;
	s_clip_rect.w = p_game_object->p_atlas_entry->w;
	s_clip_rect.h = p_game_object->p_atlas_entry->h;

	s_tex_rect.x = (int)p_game_object->transform->x;
	s_tex_rect.y = (int)p_game_object->transform->y;
	s_tex_rect.w = (int)p_game_object->transform->w;
	s_tex_rect.h = (int)p_game_object->transform->h;

	SDL_RenderCopyEx(
		g_gpu_renderer,
		g_main_atlas_texture,
		&s_clip_rect, 
		&s_tex_rect,
		p_game_object->angle,
		NULL,
		g_flip_type
	);
}


void gfx_clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	// Set the color to cornflower blue and clear
	SDL_SetRenderDrawColor(g_gpu_renderer, r, g, b, a);
	SDL_RenderClear(g_gpu_renderer);
}


void gfx_present()
{
	// Show the renderer contents
	SDL_RenderPresent(g_gpu_renderer);
}

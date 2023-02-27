#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>

#include <SDL.h>
#include <SDL_image.h>

#include "../game/game_object.h"


SDL_Renderer* g_gpu_renderer;
SDL_Texture* g_main_atlas_texture;
SDL_RendererFlip g_flip_type;

void gfx_init_renderer(const SDL_Window* p_window);
void gfx_load_main_atlas_texture(const char* p_path);
void gfx_render_gameobject(const Game_Object* p_game_object);

void gfx_clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void gfx_present();

#endif

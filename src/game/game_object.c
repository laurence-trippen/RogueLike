#include "game_object.h"

#include <stdlib.h>

#include "../gfx/texture_atlas.h"

Game_Object* game_create_gameobject(const char* atlas_id, const GFX_Texture_Atlas* p_atlas_data)
{
	Game_Object* game_object = (Game_Object*)malloc(sizeof(Game_Object));

	if (game_object == NULL) return NULL;

	game_object->transform = (SDL_FRect*) malloc(sizeof(SDL_FRect));

	game_object->p_atlas_entry = gfx_find_atlas_entry_by_id(p_atlas_data, atlas_id);
	game_object->transform->w = game_object->p_atlas_entry->w;
	game_object->transform->h = game_object->p_atlas_entry->h;
	game_object->transform->x = 0.0f;
	game_object->transform->y = 0.0f;
	game_object->angle = 0.0;

	return game_object;
}

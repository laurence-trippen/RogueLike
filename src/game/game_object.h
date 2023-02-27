#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL.h>

#include "../gfx/texture_atlas.h"


typedef struct Game_Object {
	GFX_Texture_Atlas_Entry* p_atlas_entry;
	SDL_FRect* transform;
	double angle;
} Game_Object;


Game_Object* game_create_gameobject(const char* atlas_id, const GFX_Texture_Atlas* p_atlas_data);

#endif

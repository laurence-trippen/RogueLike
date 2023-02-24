#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include <stdint.h>


typedef struct GFX_Texture_Atlas_Entry {
	char* title;
	uint32_t x, y, w, h;
	uint8_t frames;
} GFX_Texture_Atlas_Entry;


typedef struct GFX_Texture_Atlas {
	size_t length;
	GFX_Texture_Atlas_Entry* entries; // Pointer to an array memory block.
} GFX_Texture_Atlas;


GFX_Texture_Atlas* gfx_load_texture_atlas(const char* path);
void gfx_debug_print_atlas(GFX_Texture_Atlas* p_atlas);


#endif


#include "default.h"
#include "util/log.h"

#include <SDL2/SDL.h>


#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>

extern SDL_Renderer *renderer;

static TTF_Font *fonts[MAX_FONT_SIZE + 1];

void initFont() {
	TTF_Init();
	fonts[DEFAULT_FONT_SIZE] = TTF_OpenFont(DEFAULT_FONT_PATH, DEFAULT_FONT_SIZE);
	Assert(fonts[DEFAULT_FONT_SIZE] != NULL, "TTF_OpenFont: %s", TTF_GetError());
}

static TTF_Font *getFont(int ptsize) {
	if (fonts[ptsize] == NULL) {
		fonts[ptsize] = TTF_OpenFont(DEFAULT_FONT_PATH, ptsize);
		Assert(fonts[ptsize] != NULL, "TTF_OpenFont: %s", TTF_GetError());
	}
	return fonts[ptsize];
}

SDL_Texture *createText(const char *text, int ptsize, SDL_Color color) {

	SDL_Surface *surface = TTF_RenderUTF8_Blended(getFont(ptsize), text, color);
	Cannot(surface == NULL);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	Cannot(texture == NULL);

	SDL_FreeSurface(surface);
	return texture;
}


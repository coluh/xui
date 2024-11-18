
#include "default.h"
#include "font.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

SDL_Window *window;
SDL_Renderer *renderer;

void xuiInit() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE,
			&window, &renderer);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	initFont();
}

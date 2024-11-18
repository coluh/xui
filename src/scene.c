#include "../include/xui.h"
#include "util/alloc.h"
#include "util/common.h"
#include "util/log.h"
#include "default.h"
#include "calculate.h"
// #include "bridge.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <string.h>

extern SDL_Window *window;
extern SDL_Renderer *renderer;

typedef struct xuiScece {
	Widget root;
	char *title;
} xuiScene;

typedef xuiScene *Scene;

Scene xuiCreateScene(Widget widget) {
	Scene scene = callo(1, sizeof(xuiScene));
	scene->root = widget;
	return scene;
}

void xuiSetSceneTitle(Scene scene, const char *title) {
	scene->title = strdup(title);
}

void xuiStartScene(Scene scene) {

	scene->root->x = 0;
	scene->root->y = 0;
	calculatePosition(scene->root);
	scene->root->width = MAX(scene->root->width, DEFAULT_WINDOW_WIDTH);
	scene->root->height = MAX(scene->root->height, DEFAULT_WINDOW_HEIGHT);
	SDL_SetWindowSize(window, scene->root->width, scene->root->height);

	SDL_Event event;
	bool running = true;
	while (running) {
		Uint32 start = SDL_GetTicks();

		// while (SDL_PollEvent(&event)) {
		SDL_WaitEvent(&event);{
			if (event.type == SDL_QUIT)
				running = false;
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
				scene->root->width = event.window.data1;
				scene->root->height = event.window.data2;
				calculatePosition(scene->root);
			}
			scene->root->handler(scene->root, &event);
		}

		// updateWidget(scene->root);

		SDL_SetRenderDrawColor(renderer, colorUnpack(DEFAULT_BGCOLOR));
		SDL_RenderClear(renderer);
		scene->root->render(scene->root);
		SDL_RenderPresent(renderer);

		Uint32 end = SDL_GetTicks();
		if (end - start < 1000/FPS) {
			// SDL_Delay(1000/FPS - (end - start));
		}
	}
}

void xuiDestroyScene(Scene scene) {
	if (scene->title)
		free(scene->title);

	//  destroy widget...

	free(scene);
}

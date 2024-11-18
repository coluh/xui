#include "togglebutton.h"
#include "../util/common.h"
#include "../font.h"
#include "../default.h"
#include "base/style.h"
#include "base/widget.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <stdbool.h>
#include <string.h>

extern SDL_Renderer *renderer;

static void render(xuiWidget *self) {
	renderBorderBackground(self);

	xuiToggleButton *tb = (void*)self;
	SDL_SetRenderDrawColor(renderer, colorUnpack(tb->style.fgColor));
	SDL_Rect rect = {
		.x = tb->base.x + tb->style.border.l,
		.y = tb->base.y + tb->style.border.t,
		.w = DEFAULT_BLANKSIZE,
		.h = DEFAULT_BLANKSIZE,
	};
	if (tb->selected) {
		rect.x += DEFAULT_BLANKSIZE;
	}
	SDL_RenderFillRect(renderer, &rect);
}

static void handler(xuiWidget *self, SDL_Event *event) {
	xuiToggleButton *tb = (xuiToggleButton *)self;
	if (event->type == SDL_MOUSEBUTTONDOWN) {
		int mx = event->button.x;
		int my = event->button.y;
		if (inRect(mx, my, Rect(tb->base.x, tb->base.y, tb->base.width, tb->base.height))) {
			tb->selected = tb->selected ? false : true;
			tb->callback(self, tb->selected, NULL);
		}
	}
}

Widget xuiCreateToggleButton(bool selected, OnSelectedCallback callback) {
	xuiToggleButton *tb = getDefaultWidget(sizeof(xuiToggleButton));
	setDefaultStyle(&tb->style);
	tb->base.type = Widget_ToggleButton;
	tb->base.render = render;
	tb->base.handler = handler;
	tb->style.border = xuiInsets(10, 10, 10, 10);

	tb->selected = selected;
	tb->callback = callback;
	tb->base.width = DEFAULT_BLANKSIZE * 2 + BORDERS_H(tb->style);
	tb->base.height = DEFAULT_BLANKSIZE + BORDERS_V(tb->style);

	return (xuiWidget *)tb;
}




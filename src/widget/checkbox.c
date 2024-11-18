#include "checkbox.h"
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

	xuiCheckBox* c = (xuiCheckBox*)self;
	renderTextOff(self, c->texture, DEFAULT_BLANKSIZE, 0);

	SDL_SetRenderDrawColor(renderer, colorUnpack(c->style.fgColor));
	SDL_Rect rect = {
		.x = c->base.x + c->style.padding.l + c->style.border.l,
		.y = c->base.y + c->style.padding.t + c->style.border.t,
		.w = DEFAULT_BLANKSIZE,
		.h = DEFAULT_BLANKSIZE,
	};
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, colorUnpack(c->style.bgColor));
	rect.x += DEFAULT_BORDERSIZE;
	rect.y += DEFAULT_BORDERSIZE;
	rect.w -= DEFAULT_BORDERSIZE * 2;
	rect.h -= DEFAULT_BORDERSIZE * 2;
	SDL_RenderFillRect(renderer, &rect);

	if (c->selected) {
		// draw a \/
		SDL_SetRenderDrawColor(renderer, colorUnpack(c->style.fgColor));
		SDL_RenderFillRect(renderer, &rect);
	}
}

static void handler(xuiWidget *self, SDL_Event *event) {
	xuiCheckBox *c = (xuiCheckBox*)self;
	if (event->type == SDL_MOUSEBUTTONDOWN) {
		int mx = event->button.x;
		int my = event->button.y;
		if (inRect(mx, my, Rect(c->base.x, c->base.y, c->base.width, c->base.height))) {
			c->selected = c->selected ? false : true;
		}
	}
}

Widget xuiCreateCheckBox(const char *text, bool selected) {
	xuiCheckBox *c = getDefaultWidget(sizeof(xuiCheckBox));
	setDefaultStyle(&c->style);
	c->base.type = Widget_CheckBox;
	c->base.render = render;
	c->base.handler = handler;

	c->text = strdup(text);
	c->texture = createText(c->text, c->style.fontSize, c->style.fgColor);
	c->selected = selected;
	SDL_QueryTexture(c->texture, NULL, NULL, &c->base.width, &c->base.height);
	c->base.width += c->style.padding.l + c->style.padding.r + c->style.border.l + c->style.border.r;
	c->base.width += DEFAULT_BLANKSIZE;
	c->base.height += c->style.padding.t + c->style.padding.b + c->style.border.t + c->style.border.b;

	return (xuiWidget *)c;
}


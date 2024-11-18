#include "button.h"
#include "../util/common.h"
#include "../font.h"
#include "base/style.h"
#include "base/widget.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <string.h>

extern SDL_Renderer *renderer;

static void render(xuiWidget *self) {
	renderBorderBackground(self);
	renderText(self, ((xuiButton*)self)->texture);
}

static void handler(xuiWidget *self, SDL_Event *event) {
	xuiButton *b = (xuiButton *)self;
	if (event->type == SDL_MOUSEBUTTONDOWN) {
		int mx = event->button.x;
		int my = event->button.y;
		if (inRect(mx, my, Rect(b->base.x, b->base.y, b->base.width, b->base.height))) {
			b->callback(self, NULL);
		}
	}
}

Widget xuiCreateButton(const char *text, OnClickCallback callback) {
	xuiButton *b = getDefaultWidget(sizeof(xuiButton));
	setDefaultStyle(&b->style);
	b->base.type = Widget_Button;
	b->style.border = (Insets){5,5,5,5};
	b->base.render = render;
	b->base.handler = handler;

	b->text = strdup(text);
	b->callback = callback;

	b->texture = createText(b->text, b->style.fontSize, b->style.fgColor);
	SDL_QueryTexture(b->texture, NULL, NULL, &b->base.width, &b->base.height);
	b->base.width += b->style.padding.l + b->style.padding.r + b->style.border.l + b->style.border.r;
	b->base.height += b->style.padding.t + b->style.padding.b + b->style.border.t + b->style.border.b;

	return (xuiWidget *)b;
}



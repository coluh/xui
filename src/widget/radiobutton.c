#include "radiobutton.h"
#include "base/widget.h"

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

	xuiRadioButton *rb = (xuiRadioButton*)self;
	renderTextOff(self, rb->texture, DEFAULT_BLANKSIZE, 0);

	SDL_SetRenderDrawColor(renderer, colorUnpack(rb->style.fgColor));
	SDL_Rect rect = {
		.x = rb->base.x + rb->style.padding.l + rb->style.border.l,
		.y = rb->base.y + rb->style.padding.t + rb->style.border.t,
		.w = DEFAULT_BLANKSIZE,
		.h = DEFAULT_BLANKSIZE,
	};
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, colorUnpack(rb->style.bgColor));
	rect.x += DEFAULT_BORDERSIZE;
	rect.y += DEFAULT_BORDERSIZE;
	rect.w -= DEFAULT_BORDERSIZE * 2;
	rect.h -= DEFAULT_BORDERSIZE * 2;
	SDL_RenderFillRect(renderer, &rect);

	if (rb->selected) {
		// draw a \/
		SDL_SetRenderDrawColor(renderer, colorUnpack(rb->style.fgColor));
		SDL_RenderFillRect(renderer, &rect);
	}
}

static void selectRadio(xuiRadioButton *rb) {
	rb->selected = true;
	for (xuiWidget *v = iterWidget(); v != NULL; v = nextWidget()) {
		if (v->type != Widget_RadioButton)
			continue;
		xuiRadioButton *vrb = (void*)v;
		if (vrb->groupId != rb->groupId)
			continue;
		if (vrb->base.id != rb->base.id)
			vrb->selected = false;
	}
}

static void handler(xuiWidget *self, SDL_Event *event) {
	xuiRadioButton *rb = (xuiRadioButton*)self;
	if (event->type == SDL_MOUSEBUTTONDOWN) {
		int mx = event->button.x;
		int my = event->button.y;
		if (inRect(mx, my, Rect(rb->base.x, rb->base.y, rb->base.width, rb->base.height))) {
			if (rb->selected == false) {
				selectRadio(rb);
			}
		}
	}
}

Widget xuiCreateRadioButton(const char *text, bool selected, int groupId) {
	xuiRadioButton *rb = getDefaultWidget(sizeof(xuiRadioButton));
	setDefaultStyle(&rb->style);
	rb->base.type = Widget_RadioButton;
	rb->base.render = render;
	rb->base.handler = handler;

	rb->text = strdup(text);
	rb->texture = createText(rb->text, rb->style.fontSize, rb->style.fgColor);
	rb->selected = selected;
	SDL_QueryTexture(rb->texture, NULL, NULL, &rb->base.width, &rb->base.height);
	rb->base.width += rb->style.padding.l + rb->style.padding.r + rb->style.border.l + rb->style.border.r;
	rb->base.width += DEFAULT_BLANKSIZE;
	rb->base.height += rb->style.padding.t + rb->style.padding.b + rb->style.border.t + rb->style.border.b;

	return (xuiWidget *)rb;
}


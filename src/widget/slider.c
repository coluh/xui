#include "slider.h"
#include "../util/common.h"
#include "../util/alloc.h"
#include "../util/log.h"
#include "../font.h"
#include "../default.h"
#include "base/style.h"
#include "base/widget.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include <string.h>

extern SDL_Renderer *renderer;

static void render(xuiWidget *self) {
	renderBorderBackground(self);

	xuiSlider *s = (void*)self;
	int my = s->base.y + s->base.height/2;
	SDL_Rect rect = {
		.x = s->base.x + s->style.border.l + s->style.padding.l,
		.y = my - DEFAULT_BORDERSIZE * 2,
		.w = s->base.width - BORDERS_H(s->style) - PADDINGS_H(s->style),
		.h = DEFAULT_BORDERSIZE * 4,
	};
	SDL_SetRenderDrawColor(renderer, colorUnpack(s->style.fgColor));
	SDL_RenderFillRect(renderer, &rect);
	rect.x += DEFAULT_BORDERSIZE;
	rect.y += DEFAULT_BORDERSIZE;
	rect.w -= DEFAULT_BORDERSIZE * 2;
	rect.h -= DEFAULT_BORDERSIZE * 2;
	SDL_SetRenderDrawColor(renderer, colorUnpack(s->style.bgColor));
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, colorUnpack(s->style.fgColor));
	rect.x += (float)rect.w * ((s->value - s->min) / (s->max - s->min)) - DEFAULT_BLANKSIZE/2.0f;
	rect.y = my - DEFAULT_BLANKSIZE/2;
	rect.w = DEFAULT_BLANKSIZE;
	rect.h = DEFAULT_BLANKSIZE;
	SDL_RenderFillRect(renderer, &rect);
}

static void updateValue(xuiSlider *s, int mx) {
	int x = s->base.x + s->style.border.l + s->style.padding.l + DEFAULT_BORDERSIZE;
	int w = s->base.width - BORDERS_H(s->style) - PADDINGS_H(s->style) - DEFAULT_BORDERSIZE * 2;
	float value = (float)(mx - x) / w * (s->max - s->min) + s->min;
	value = MAX(value, s->min);
	value = MIN(value, s->max);

	float v = s->min;
	for (; v < s->max; v += s->step) {
		if (v > value)
			break;
	}
	if (v - value <= s->step / 2) {
		value = v;
	} else {
		value = v - s->step;
	}
	value = MIN(value, s->max);
	s->value = value;
}

static void handler(xuiWidget *self, SDL_Event *event) {
	xuiSlider *s = (void*)self;
	if (event->type == SDL_MOUSEBUTTONDOWN) {
		int mx = event->button.x;
		int my = event->button.y;
		if (inRect(mx, my, Rect(s->base.x, s->base.y, s->base.width, s->base.height))) {
			s->sliding = true;
			updateValue(s, mx);
		}
	} else if (event->type == SDL_MOUSEMOTION) {
		int mx = event->motion.x;
		int my = event->motion.y;
		if (inRect(mx, my, Rect(s->base.x, s->base.y, s->base.width, s->base.height))) {
			if (s->sliding)
				updateValue(s, mx);
		}
	} else if (event->type == SDL_KEYUP) {
		s->sliding = false;
	}
}

Widget xuiCreateSlider(float min, float max, float step) {
	xuiSlider *s = getDefaultWidget(sizeof(xuiSlider));
	setDefaultStyle(&s->style);
	s->base.type = Widget_Slider;
	s->base.render = render;
	s->base.handler = handler;

	s->min = min;
	s->max = max;
	s->step = step;

	s->value = s->min;
	s->base.width = 200;
	s->base.height = DEFAULT_FONT_SIZE;

	return (xuiWidget *)s;
}

float xuiSliderGetValue(Widget slider) { return ((xuiSlider*)slider)->value; }


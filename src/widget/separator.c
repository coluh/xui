#include "separator.h"
#include "../util/common.h"
#include "base/style.h"
#include "base/widget.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

extern SDL_Renderer *renderer;

static void render(xuiWidget *self) {
	xuiSeparator *s = (xuiSeparator*)self;
	renderBorderBackground(self);
	int my = s->base.y + (s->base.height)/2;
	SDL_SetRenderDrawColor(renderer, colorUnpack(s->style.fgColor));
	SDL_RenderDrawLine(renderer, s->base.x, my, s->base.x + s->base.width, my);
}

static void handler(xuiWidget *self, SDL_Event *event) {}

Widget xuiCreateSeparator() {
	xuiSeparator *s = getDefaultWidget(sizeof(xuiSeparator));
	setDefaultStyle(&s->style);
	s->base.type = Widget_Separator;
	s->base.render = render;
	s->base.handler = handler;

	return (xuiWidget *)s;
}




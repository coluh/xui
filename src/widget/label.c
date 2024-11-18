#include "label.h"
#include "base/style.h"
#include "base/widget.h"
#include "../font.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <string.h>

extern SDL_Renderer *renderer;

static void render(xuiWidget *self) {
	renderBorderBackground(self);
	renderText(self, ((xuiLabel*)self)->texture);
}

static void handler(xuiWidget *self, SDL_Event *event) {}

Widget xuiCreateLabel(const char *text) {
	xuiLabel *l = getDefaultWidget(sizeof(xuiLabel));
	setDefaultStyle(&l->style);
	l->base.type = Widget_Label;
	l->base.render = render;
	l->base.handler = handler;

	l->text = strdup(text);
	l->texture = createText(l->text, l->style.fontSize, l->style.fgColor);
	SDL_QueryTexture(l->texture, NULL, NULL, &l->base.width, &l->base.height);
	l->base.width += l->style.padding.l + l->style.padding.r + l->style.border.l + l->style.border.r;
	l->base.height += l->style.padding.t + l->style.padding.b + l->style.border.t + l->style.border.b;

	return (xuiWidget *)l;
}


#include "text.h"
#include "base/style.h"
#include "base/widget.h"
#include "../font.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <string.h>

extern SDL_Renderer *renderer;

static void render(xuiWidget *self) {
	renderBorderBackground(self);
	renderText(self, ((xuiText*)self)->texture);
}

static void handler(xuiWidget *self, SDL_Event *event) {}

Widget xuiCreateText(const char *text) {
	xuiText *t = getDefaultWidget(sizeof(xuiText));
	setDefaultStyle(&t->style);
	t->base.type = Widget_Text;
	t->base.render = render;
	t->base.handler = handler;

	t->text = strdup(text);
	// TODO: wrap!
	t->texture = createText(t->text, t->style.fontSize, t->style.fgColor);
	SDL_QueryTexture(t->texture, NULL, NULL, &t->base.width, &t->base.height);
	t->base.width += t->style.padding.l + t->style.padding.r + t->style.border.l + t->style.border.r;
	t->base.height += t->style.padding.t + t->style.padding.b + t->style.border.t + t->style.border.b;

	return (xuiWidget *)t;
}

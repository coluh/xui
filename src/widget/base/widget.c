#include "widget.h"
#include "style.h"

#include "../../util/alloc.h"
#include "../../util/common.h"
#include "../../util/log.h"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

static struct WidgetNode {
	xuiWidget *v;
	struct WidgetNode *next;
} *pool;

static struct WidgetNode *iter;

xuiWidget *iterWidget() {
	iter = pool;
	return iter->v;
}

xuiWidget *nextWidget() {
	iter = iter->next;
	if (iter == NULL)
		return NULL;
	return iter->v;
}

void *getDefaultWidget(int size) {
	static int id = 0;

	xuiWidget *v = callo(1, size);
	v->id = id;
	id++;

	struct WidgetNode **p;
	for (p = &pool; (*p) != NULL; p = &(*p)->next);
	(*p) = callo(1, sizeof(struct WidgetNode));
	(*p)->v = v;

	return v;
}

extern SDL_Renderer *renderer;

void renderBackground(xuiWidget *v) {
	xuiStyle *style = (xuiStyle*)&v[1];
	SDL_SetRenderDrawColor(renderer, colorUnpack(style->bgColor));
	SDL_RenderFillRect(renderer, &(SDL_Rect){v->x, v->y, v->width, v->height});
}

void renderBorderBackground(xuiWidget *v) {
	xuiStyle *style = (xuiStyle*)&v[1];
	SDL_SetRenderDrawColor(renderer, colorUnpack(style->fgColor));
	SDL_RenderFillRect(renderer, &(SDL_Rect){v->x, v->y, v->width, v->height});

	SDL_SetRenderDrawColor(renderer, colorUnpack(style->bgColor));
	SDL_Rect rect = {
		.x = v->x + style->border.l,
		.y = v->y + style->border.t,
		.w = v->width - style->border.l - style->border.r,
		.h = v->height - style->border.t - style->border.b,
	};
	SDL_RenderFillRect(renderer, &rect);
}

void renderText(xuiWidget *v, SDL_Texture *texture) {
	xuiStyle *style = (xuiStyle*)(v+1);

	int x = v->x + style->border.l + style->padding.l;
	int y = v->y + style->border.t + style->padding.t;

	int width, height;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	SDL_RenderCopy(renderer, texture, NULL, &(SDL_Rect){x, y, width, height});
}

void renderTextOff(xuiWidget *v, SDL_Texture *texture, int offx, int offy) {
	xuiStyle *style = (xuiStyle*)(v+1);

	int x = v->x + style->border.l + style->padding.l;
	int y = v->y + style->border.t + style->padding.t;
	x += offx;
	y += offy;

	int width, height;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	SDL_RenderCopy(renderer, texture, NULL, &(SDL_Rect){x, y, width, height});
}


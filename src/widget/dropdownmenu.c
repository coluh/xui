#include "dropdownmenu.h"
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

	xuiDropdownMenu *m = (void*)self;
	SDL_SetRenderDrawColor(renderer, colorUnpack(m->style.fgColor));
	Cannot(m->items == NULL);
	if (!m->showMenu) {
		renderText(self, m->current->texture);
		int x = m->base.x + m->base.width - m->style.padding.r - m->style.border.r;
		x -= DEFAULT_BLANKSIZE;
		int y = m->base.y + m->base.height/2 - DEFAULT_BLANKSIZE/2;
		int w = DEFAULT_BLANKSIZE;
		for (; w > 0; x += 1, y += 1, w -= 2)
			SDL_RenderDrawLine(renderer, x, y, x + w, y);
	} else {
		int offy = 0;
		int ph = m->base.height - PADDINGS_V(m->style) - BORDERS_V(m->style);
		SDL_SetRenderDrawColor(renderer, colorUnpack(m->style.fgColor));
		SDL_RenderFillRect(renderer, &(SDL_Rect){ m->base.x, m->base.y, m->base.width,
				ph * m->itemsCount + PADDINGS_V(m->style) + BORDERS_V(m->style) });
		SDL_SetRenderDrawColor(renderer, colorUnpack(m->style.bgColor));
		SDL_RenderFillRect(renderer, &(SDL_Rect){ m->base.x + m->style.border.l, m->base.y + m->style.border.t,
				m->base.width - BORDERS_H(m->style), ph * m->itemsCount + PADDINGS_V(m->style) });
		SDL_SetRenderDrawColor(renderer, colorUnpack(m->style.fgColor));
		for (struct ItemNode *p = m->items; p != NULL; p = p->next) {
			renderTextOff(self, p->texture, 0, offy);
			offy += ph;
		}
	}

	// render triangle
}

static void handler(xuiWidget *self, SDL_Event *event) {
	xuiDropdownMenu *m = (void*)self;
	if (event->type == SDL_MOUSEBUTTONDOWN) {
		int mx = event->button.x;
		int my = event->button.y;
		if (!m->showMenu) {
			if (inRect(mx, my, Rect(m->base.x, m->base.y, m->base.width, m->base.height))) {
				m->showMenu = true;
			}
		} else {
			int x = m->base.x + m->style.border.l + m->style.padding.l;
			int y = m->base.y + m->style.border.t + m->style.padding.t;
			int w = m->base.width - BORDERS_H(m->style) - PADDINGS_H(m->style);
			int h = m->base.height - BORDERS_V(m->style) - PADDINGS_V(m->style);
			for (struct ItemNode *p = m->items; p != NULL; p = p->next) {
				if (inRect(mx, my, Rect(x, y, w, h))) {
					m->current = p;
					m->showMenu = false;
					break;
				}
				y += h;
			}
			m->showMenu = false;
		}
	}
}

Widget xuiCreateDropdownMenu(int itemSize, ToStringCallback callback) {
	xuiDropdownMenu *m = getDefaultWidget(sizeof(xuiDropdownMenu));
	setDefaultStyle(&m->style);
	m->base.type = Widget_DropdownMenu;
	m->base.render = render;
	m->base.handler = handler;

	m->itemSize = itemSize;
	m->toString = callback;

	m->showMenu = false;
	m->base.height = DEFAULT_FONT_SIZE;

	return (xuiWidget *)m;
}

void xuiDropdownMenuAddData(Widget dropdownMenu, void *dataList, int count) {
	xuiDropdownMenu *m = (void*)dropdownMenu;
	Assert(m->items == NULL, "dont add data twice to menu");

	int maxW = 0, maxH = 0;
	struct ItemNode **pp = &m->items;
	for (int i = 0; i < count; i++) {
		*pp = callo(1, sizeof(struct ItemNode) + m->itemSize);
		struct ItemNode *this = *pp;

		void *ai = dataList + i * m->itemSize;
		memcpy(this->item, ai, m->itemSize);
		this->text = strdup(m->toString(this->item));
		Debug("%s Added", this->text);
		this->texture = createText(this->text, m->style.fontSize, m->style.fgColor);

		int width, height;
		SDL_QueryTexture(this->texture, NULL, NULL, &width, &height);
		maxW = MAX(maxW, width);
		maxH = MAX(maxH, height);

		pp = &(*pp)->next;
	}

	m->base.width = maxW + DEFAULT_BLANKSIZE + PADDINGS_H(m->style) + BORDERS_H(m->style);
	m->base.height = maxH + PADDINGS_V(m->style) + BORDERS_V(m->style);
	m->current = m->items;
	m->itemsCount = count;
}


#include "linearlayout.h"
#include "base/style.h"
#include "base/widget.h"
#include "../util/alloc.h"
#include "../util/common.h"
#include "../default.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

extern SDL_Renderer *renderer;

static void render(xuiWidget *self) {
	renderBorderBackground(self);
	xuiLinearLayout *ll = (xuiLinearLayout*)self;

	for (int i = 0; i < ll->childrenCount; i++) {
		ll->children[i]->render(ll->children[i]);
	}
}

static void handler(xuiWidget *self, SDL_Event *event) {
	xuiLinearLayout *ll = (xuiLinearLayout*)self;
	for (int i = 0; i < ll->childrenCount; i++) {
		ll->children[i]->handler(ll->children[i], event);
	}
}

Widget xuiCreateLinearLayout(Orientation orient, Widget children[], int count) {
	xuiLinearLayout *ll = getDefaultWidget(sizeof(xuiLinearLayout));
	setDefaultStyle(&ll->style);
	ll->base.type = Widget_LinearLayout;
	ll->base.render = render;
	ll->base.handler = handler;

	ll->style.bgColor = xuiColor(200, 200, 240, 255);

	ll->orient = orient;
	ll->arrange = Arrange_SpaceBetween;
	ll->gap = DEFAULT_GAP;
	ll->childrenCount = count;
	ll->children = callo(count, sizeof(xuiWidget*));
	for (int i = 0; i < count; i++) {
		ll->children[i] = children[i];
		xuiWidget *v = children[i];
		v->parent = (xuiWidget*)ll;
		((xuiStyle*)(v+1))->bgColor = xuiColor(200, 240, 240, 255);
		if (v->type == Widget_Separator) {
			if (orient == Orientation_Horizontal)
				v->height = DEFAULT_GAP;
			else
				v->width = DEFAULT_GAP;
		}
	}

	return (xuiWidget *)ll;
}


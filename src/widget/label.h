#ifndef XUI_widget_label_h
#define XUI_widget_label_h

#include "../../include/xui.h"
#include "base/widget.h"
#include "base/style.h"
#include <SDL2/SDL_render.h>
#include <stdbool.h>

typedef struct xuiLabel {
	xuiWidget base;
	xuiStyle style;

	char *text;
	SDL_Texture *texture;
} xuiLabel;

Widget xuiCreateLabel(const char *text);

#endif

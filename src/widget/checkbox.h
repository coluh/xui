#ifndef XUI_widget_checkbox_h
#define XUI_widget_checkbox_h

#include "../../include/xui.h"
#include "base/widget.h"
#include "base/style.h"
#include <stdbool.h>
#include <SDL2/SDL_render.h>

typedef struct xuiCheckBox {
	xuiWidget base;
	xuiStyle style;

	char *text;
	SDL_Texture *texture;

	bool selected;
} xuiCheckBox;

Widget xuiCreateCheckBox(const char *text, bool selected);

#endif

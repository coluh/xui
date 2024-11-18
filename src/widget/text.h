#ifndef XUI_widget_text_h
#define XUI_widget_text_h

#include "../../include/xui.h"
#include "base/widget.h"
#include "base/style.h"
#include <SDL2/SDL_render.h>

typedef struct xuiText {
	xuiWidget base;
	xuiStyle style;

	char *text;
	SDL_Texture *texture;
} xuiText;

Widget xuiCreateText(const char *text);

#endif

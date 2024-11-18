#ifndef XUI_widget_button_h
#define XUI_widget_button_h

#include "../../include/xui.h"
#include "base/widget.h"
#include "base/style.h"
#include <SDL2/SDL_render.h>

typedef struct xuiButton {
	xuiWidget base;
	xuiStyle style;

	char *text;
	SDL_Texture *texture;

	OnClickCallback callback;
} xuiButton;

Widget xuiCreateButton(const char *text, OnClickCallback callback);

#endif

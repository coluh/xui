#ifndef XUI_widget_separator_h
#define XUI_widget_separator_h

#include "../../include/xui.h"
#include "base/widget.h"
#include "base/style.h"
#include <SDL2/SDL_render.h>

typedef struct xuiSeparator {
	xuiWidget base;
	xuiStyle style;
} xuiSeparator;

Widget xuiCreateSeparator();

#endif

#ifndef XUI_widget_togglebutton_h
#define XUI_widget_togglebutton_h

#include "../../include/xui.h"
#include "base/widget.h"
#include "base/style.h"
#include <stdbool.h>
#include <SDL2/SDL_render.h>

typedef struct xuiToggleButton {
	xuiWidget base;
	xuiStyle style;

	bool selected;
	OnSelectedCallback callback;
} xuiToggleButton;

Widget xuiCreateToggleButton(bool selected, OnSelectedCallback callback);

#endif

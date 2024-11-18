#ifndef XUI_widget_radiobutton_h
#define XUI_widget_radiobutton_h

#include "../../include/xui.h"
#include "base/style.h"
#include "base/widget.h"
#include <SDL2/SDL_render.h>


typedef struct xuiRadioButton {
	xuiWidget base;
	xuiStyle style;

	char *text;
	SDL_Texture *texture;

	bool selected;
	int groupId;
} xuiRadioButton;

Widget xuiCreateRadioButton(const char *text, bool selected, int groupId);

#endif

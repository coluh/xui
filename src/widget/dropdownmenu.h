#ifndef XUI_widget_dropdownmenu_h
#define XUI_widget_dropdownmenu_h

#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include "../../include/xui.h"
#include "base/widget.h"
#include "base/style.h"

struct ItemNode {
	struct ItemNode *next;
	char *text;
	SDL_Texture *texture;
	char item[];
};

typedef struct xuiDropdownMenu {
	xuiWidget base;
	xuiStyle style;

	int itemSize;
	ToStringCallback toString;

	struct ItemNode *items;
	struct ItemNode *current;
	int itemsCount;
	bool showMenu;
} xuiDropdownMenu;

Widget xuiCreateDropdownMenu(int itemSize, ToStringCallback callback);
void xuiDropdownMenuAddData(Widget dropdownMenu, void *dataList, int count);

#endif

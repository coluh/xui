#ifndef XUI_widget_base_widget_h
#define XUI_widget_base_widget_h

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

typedef enum xuiWidgetType {
	Widget_Button,
	Widget_Label,
	Widget_LinearLayout,
	Widget_Text,
} xuiWidgetType;

#ifndef NDEBUG
static const char *widgetTypes[] = {
	"Button", "Label", "LinearLayout", "Text",
};
#endif

typedef struct xuiWidget *Widget;

typedef struct xuiWidget {
	int id;
	int x, y;
	int width, height;
	void (*render)(Widget self);
	void (*handler)(Widget self, SDL_Event *event);
	struct xuiWidget *parent;
	xuiWidgetType type;
} xuiWidget;

typedef xuiWidget *Widget;

void *getDefaultWidget(int size);
void renderBackground(xuiWidget *v);
void renderBorderBackground(xuiWidget *v);
void renderText(xuiWidget *v, SDL_Texture *texture);

#endif

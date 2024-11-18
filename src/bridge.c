#include "bridge.h"
#include "../include/xui.h"
#include "font.h"
#include "util/log.h"
#include "widget/base/style.h"
#include "widget/base/widget.h"
#include "widget/linearlayout.h"

#include <SDL2/SDL_render.h>

void updateWidget(xuiWidget *widget) {
	;
}


void xuiSetProperty(Widget widget, Property property, int *value) {
	xuiStyle *style = (xuiStyle*)(widget+1);
	Insets insets;
	switch (property) {
	case Property_Width:
		widget->width = value[0];
		break;
	case Property_Height:
		widget->height = value[0];
		break;
	case Property_Padding:
		insets = style->padding;
		style->padding = xuiInsets(value[0], value[0], value[0], value[0]);
		widget->width += style->padding.l - insets.l + style->padding.r - insets.r;
		widget->height += style->padding.t - insets.t + style->padding.b - insets.b;
		break;
	case Property_Zindex:
		style->z_index = value[0];
		break;
	case Property_FgColor:
		style->fgColor = xuiColor(value[0], value[1], value[2], value[3]);
		if (widget->type == Widget_Text || widget->type == Widget_Button || widget->type == Widget_Label) {
			struct { xuiWidget b; xuiStyle s; char *t; SDL_Texture *texture; } *v = (void*)widget;
			SDL_DestroyTexture(v->texture);
			v->texture = createText(v->t, style->fontSize, style->fgColor);
		}
		break;
	case Property_BgColor:
		style->bgColor = xuiColor(value[0], value[1], value[2], value[3]);
		break;
	case Property_Align:
		style->align = value[0];
		break;
	case Property_Arrange:
		if (widget->type == Widget_LinearLayout) {
			xuiLinearLayout *ll = (xuiLinearLayout*)widget;
			ll->arrange = value[0];
		} else {
			NotImplemented();
		}
		break;
	case Property_Orientation:
		NotImplemented();
		break;
	default:
		NotImplemented();
		break;
	}
}




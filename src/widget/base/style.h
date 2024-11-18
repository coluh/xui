#ifndef XUI_widget_base_style_h
#define XUI_widget_base_style_h

#include "../../../include/xui.h"

typedef struct xuiStyle {
	int fontSize;
	Align align;
	Insets padding;
	Insets border;
	Color fgColor, bgColor;
	int z_index;
} xuiStyle;

void setDefaultStyle(xuiStyle *s);

#endif

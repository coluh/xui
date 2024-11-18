#ifndef XUI_widget_base_style_h
#define XUI_widget_base_style_h

#include "../../../include/xui.h"

#define PADDINGS_H(p) ((p).padding.l + (p).padding.r)
#define BORDERS_H(p) ((p).border.l + (p).border.r)
#define PADDINGS_V(p) ((p).padding.t + (p).padding.b)
#define BORDERS_V(p) ((p).border.t + (p).border.b)

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

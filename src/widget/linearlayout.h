#ifndef XUI_widget_linearlayout_h
#define XUI_widget_linearlayout_h

#include "../../include/xui.h"
#include "base/style.h"
#include "base/widget.h"

typedef struct xuiLinearLayout {
	xuiWidget base;
	xuiStyle style;

	Orientation orient;
	Arrange arrange;
	int gap;
	xuiWidget **children;
	int childrenCount;
} xuiLinearLayout;

Widget xuiCreateLinearLayout(Orientation orient, Widget children[], int count);

#endif

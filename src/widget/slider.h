#ifndef XUI_widget_slider_h
#define XUI_widget_slider_h

#include "../../include/xui.h"
#include "base/widget.h"
#include "base/style.h"

typedef struct xuiSlider {
	xuiWidget base;
	xuiStyle style;

	float min;
	float max;
	float step;

	float value;
	bool sliding;
} xuiSlider;

Widget xuiCreateSlider(float min, float max, float step);
float xuiSliderGetValue(Widget slider);

#endif

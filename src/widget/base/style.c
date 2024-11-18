#include "style.h"
#include "widget.h"
#include "../../default.h"
#include "../../util/log.h"

void setDefaultStyle(xuiStyle *s) {
	s->fontSize = DEFAULT_FONT_SIZE;
	s->align = Align_Center;

	s->padding = (Insets) { 10, 10, 10, 10 };
	s->border = (Insets) { 2, 2, 2, 2 };

	s->fgColor = (Color) { 0, 0, 0, 255 };
	s->bgColor = (Color) { 240, 255, 255, 255 };

	// s->z_index = 0;
}


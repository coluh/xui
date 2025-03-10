#include "calculate.h"
#include <stdbool.h>
#include "widget/base/style.h"
#include "widget/base/widget.h"
#include "widget/linearlayout.h"
#include "util/common.h"
#include "util/log.h"

#define NDEBUG 114514

static int getMaxWidth(xuiWidget **children, int childrenCount) {
	int max = 0;
	for (int i = 0; i < childrenCount; i++) {
		if (max < children[i]->width)
			max = children[i]->width;
	}
	return max;
}

static int getMaxHeight(xuiWidget **children, int childrenCount) {
	int max = 0;
	for (int i = 0; i < childrenCount; i++) {
		if (max < children[i]->height)
			max = children[i]->height;
	}
	return max;
}

static int getTotalWidth(xuiWidget **children, int childrenCount) {
	int sum = 0;
	for (int i = 0; i < childrenCount; i++) {
		sum += children[i]->width;
	}
	return sum;
}

static int getTotalHeight(xuiWidget **children, int childrenCount) {
	int sum = 0;
	for (int i = 0; i < childrenCount; i++) {
		sum += children[i]->height;
	}
	return sum;
}

static void updateX(xuiWidget *widget, int newX) {
	int dx = newX - widget->x;
#ifndef NDEBUG
	DebugPrint("%s: %d -> %d", widgetTypes[widget->type], widget->x, newX);
#endif
	widget->x = newX;

	if (widget->type == Widget_LinearLayout) {
		xuiLinearLayout *ll = (xuiLinearLayout*)widget;
		for (int i = 0; i < ll->childrenCount; i++) {
			xuiWidget *v = ll->children[i];
			updateX(v, v->x + dx);
		}
	}
}

static void updateY(xuiWidget *widget, int newY) {
	int dy = newY - widget->y;
#ifndef NDEBUG
	DebugPrint("%s: %d -> %d", widgetTypes[widget->type], widget->y, newY);
#endif
	widget->y = newY;

	if (widget->type == Widget_LinearLayout) {
		xuiLinearLayout *ll = (xuiLinearLayout*)widget;
		for (int i = 0; i < ll->childrenCount; i++) {
			xuiWidget *v = ll->children[i];
			updateY(v, v->y + dy);
		}
	}
}

static bool hasGrow(Orientation orient, xuiWidget **children, int childrenCount) {
	if (orient == Orientation_Horizontal) {
		for (int i = 0; i < childrenCount; i++) {
			xuiWidget *v = children[i];
			xuiStyle *style = (xuiStyle*)(v+1);
			if ((style->align & Align_Left) && (style->align & Align_Right))
				return true;
		}
		return false;
	} else {
		for (int i = 0; i < childrenCount; i++) {
			xuiWidget *v = children[i];
			xuiStyle *style = (xuiStyle*)(v+1);
			if ((style->align & Align_Top) && (style->align & Align_Bottom))
				return true;
		}
		return false;
	}
}

static void calculateLinearLayoutPosition(xuiLinearLayout *ll) {
	int totalWidth = getTotalWidth(ll->children, ll->childrenCount);
	int totalHeight = getTotalHeight(ll->children, ll->childrenCount);
	int maxWidth = getMaxWidth(ll->children, ll->childrenCount);
	int maxHeight = getMaxHeight(ll->children, ll->childrenCount);

	int x = ll->base.x + ll->style.border.l + ll->style.padding.l;
	int y = ll->base.y + ll->style.border.t + ll->style.padding.t;

	Cannot(ll->childrenCount < 1);

	if (ll->orient == Orientation_Horizontal) {
		if (ll->base.width == 0)
			ll->base.width = totalWidth + (ll->childrenCount-1)*ll->gap + ll->style.padding.l + ll->style.padding.r;
		if (ll->base.height == 0)
			ll->base.height = maxHeight + ll->style.padding.t + ll->style.padding.b;

		int availableHeight = ll->base.height - BORDERS_V(ll->style) - PADDINGS_V(ll->style);
		for (int i = 0; i < ll->childrenCount; i++) {
			xuiWidget *v = ll->children[i];
			Align align = ((xuiStyle*)(v+1))->align;
			if (align & Align_Top) {
				updateY(v, y);
				if (align & Align_Bottom) {
					v->height = availableHeight;
				}
			} else if (align & Align_Bottom) {
				updateY(v, y + availableHeight - v->height);
			}
		}

		int availableWidth = ll->base.width - ll->style.padding.l - ll->style.padding.r;
		if (hasGrow(Orientation_Horizontal, ll->children, ll->childrenCount)) {
			int a = (PADDINGS_H(ll->style))/2;
			for (int i = 0; i < ll->childrenCount; i++) {
				xuiWidget *v = ll->children[i];
				xuiStyle *style = (xuiStyle*)(v+1);

				if ((style->align & Align_Left) && (style->align & Align_Right)) {
					// you are the one who grow...
					int width = availableWidth - (totalWidth - v->width);
					width -= a * (ll->childrenCount - 1);
					v->width = width;
				}

				updateX(v, x);
				x += v->width + a;
			};
			return;
		}
		int a;
		switch (ll->arrange) {
		case Arrange_Start:
			for (int i = 0; i < ll->childrenCount; i++) {
				xuiWidget *v = ll->children[i];
				updateX(v, x);
				x += v->width;
			}
			break;
		case Arrange_End:
			x += availableWidth - totalWidth;
			for (int i = 0; i < ll->childrenCount; i++) {
				xuiWidget *v = ll->children[i];
				updateX(v, x);
				x += v->width;
			}
			break;
		case Arrange_Center:
			x += (availableWidth - totalWidth) / 2;
			for (int i = 0; i < ll->childrenCount; i++) {
				xuiWidget *v = ll->children[i];
				updateX(v, x);
				x += v->width;
			}
			break;
		case Arrange_SpaceAround:
			a = (availableWidth - totalWidth) / (ll->childrenCount * 2);
			x += a;
			for (int i = 0; i < ll->childrenCount; i++) {
				xuiWidget *v = ll->children[i];
				updateX(v, x);
				x += v->width + 2 * a;
			}
			break;
		case Arrange_SpaceBetween:
			if (ll->childrenCount == 1) {
				xuiWidget *v = ll->children[0];
				updateX(v, x);
				break;
			}
			a = (availableWidth - totalWidth) / (ll->childrenCount - 1);
			for (int i = 0; i < ll->childrenCount; i++) {
				xuiWidget *v = ll->children[i];
				updateX(v, x);
				x += v->width + a;
			}
			break;
		case Arrange_SpaceEvenly:
			a = (availableWidth - totalWidth) / (ll->childrenCount + 1);
			x += a;
			for (int i = 0; i < ll->childrenCount; i++) {
				xuiWidget *v = ll->children[i];
				updateX(v, x);
				x += v->width + a;
			}
			break;
		}
	} else {
		if (ll->base.width == 0)
			ll->base.width = maxWidth + ll->style.padding.l + ll->style.padding.r;
		if (ll->base.height == 0)
			ll->base.height = totalHeight + (ll->childrenCount-1)*ll->gap + ll->style.padding.t + ll->style.padding.b;

		int availableWidth = ll->base.width - BORDERS_H(ll->style) - PADDINGS_H(ll->style);
		for (int i = 0; i < ll->childrenCount; i++) {
			xuiWidget *v = ll->children[i];
			Align align = ((xuiStyle*)(v+1))->align;
			if (align & Align_Left) {
				updateX(v, x);
				if (align & Align_Right) {
					v->width = availableWidth;
				}
			} else if (align & Align_Right) {
				updateX(v, x + availableWidth - v->width);
			}
		}

		int availableHeight = ll->base.height - ll->style.padding.t - ll->style.padding.b;
		if (hasGrow(Orientation_Vertical, ll->children, ll->childrenCount)) {
			int a = (PADDINGS_V(ll->style))/2;
			for (int i = 0; i < ll->childrenCount; i++) {
				xuiWidget *v = ll->children[i];
				xuiStyle *style = (xuiStyle*)(v+1);

				if ((style->align & Align_Top) & (style->align & Align_Bottom)) {
					int height = availableHeight - (totalHeight - v->height);
					height -= a * (ll->childrenCount - 1);
					v->height = height;
				}

				updateY(v, y);
				y += v->height + a;
			}
			return;
		}
		int a;
		switch (ll->arrange) {
		case Arrange_Start:
			for (int i = 0; i < ll->childrenCount; i++) {
				xuiWidget *v = ll->children[i];
				updateY(v, y);
				y += v->height;
			}
			break;
		case Arrange_End:
			y += availableHeight - totalHeight;
			for (int i = 0; i < ll->childrenCount; i++) {
				xuiWidget *v = ll->children[i];
				updateY(v, y);
				y += v->height;
			}
			break;
		case Arrange_Center:
			y += (availableHeight - totalHeight) / 2;
			for (int i = 0; i < ll->childrenCount; i++) {
				xuiWidget *v = ll->children[i];
				updateY(v, y);
				y += v->height;
			}
			break;
		case Arrange_SpaceAround:
			a = (availableHeight - totalHeight) / (ll->childrenCount * 2);
			y += a;
			for (int i = 0; i < ll->childrenCount; i++) {
				xuiWidget *v = ll->children[i];
				updateY(v, y);
				y += v->height + 2 * a;
			}
			break;
		case Arrange_SpaceBetween:
			a = (availableHeight - totalHeight) / (ll->childrenCount - 1);
			for (int i = 0; i < ll->childrenCount; i++) {
				xuiWidget *v = ll->children[i];
				updateY(v, y);
				y += v->height + a;
			}
			break;
		case Arrange_SpaceEvenly:
			a = (availableHeight - totalHeight) / (ll->childrenCount + 1);
			y += a;
			for (int i = 0; i < ll->childrenCount; i++) {
				xuiWidget *v = ll->children[i];
				updateY(v, y);
				y += v->height + a;
			}
			break;
		}
	}
}

void calculatePosition(xuiWidget *widget) {
	xuiLinearLayout *ll = (xuiLinearLayout*)widget;
	switch (widget->type) {
	case Widget_LinearLayout:
		for (int i = 0; i < ll->childrenCount; i++) {
			xuiWidget *v = ll->children[i];
			calculatePosition(v);
		}
		calculateLinearLayoutPosition(ll);
		break;
	default:
		break;
	}
#ifndef NDEBUG
	DebugPrint("%s: (%d, %d) of %d x %d", widgetTypes[widget->type], widget->x, widget->y, widget->width, widget->height);
#endif
#ifndef NDEBUG
	if (widget->type == Widget_LinearLayout) {
		for (int i = 0; i < ll->childrenCount; i++) {
			xuiWidget *v = ll->children[i];
			DebugPrint("\t%s: (%d, %d) of %d x %d", widgetTypes[v->type], v->x, v->y, v->width, v->height);
		}
	}

#endif
}


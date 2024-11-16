#ifndef XUI_H
#define XUI_H

#include <stdbool.h>
#include <stdint.h>

/*** Basic for start ***/
typedef struct WidgetSt *Widget;

typedef struct SceneSt *Scene;
Scene xuiCreateScene(Widget widget);
void xuiSetSceneTitle(Scene scene, const char *title);
void xuiStartScene(Scene scene);
void xuiDestroyScene(Scene scene);

/*** Properties ***/
#define setProperty(widget, property, ...) xuiSetProperty(widget, property, (int[]){__VA_ARGS__})
typedef enum Property {
	Property_Width,
	Property_Height,
	Property_Align,
	Property_Arrange,
	Property_Orientation,
	Property_Padding,

	Property_FgColor,
	Property_BgColor,
} Property;

void xuiSetProperty(Widget widget, Property property, int *value);

typedef enum Align {
	Align_Left	= 1 << 0,
	Align_Right	= 1 << 1,
	Align_Center	= 3,
	Align_Top	= 1 << 2,
	Align_Bottom	= 1 << 3,
} Align;

typedef enum Arrange {
	Arrange_Start,
	Arrange_Center,
	Arrange_End,
	Arrange_SpaceBetween,	// 01110
	Arrange_SpaceAround,	// 12221
	Arrange_SpaceEvenly,	// 11111
} Arrange;

typedef enum Orientation {
	Orientation_Horizontal,
	Orientation_Vertical,
} Orientation;

/*** Struct and Types ***/
typedef struct Color {
	uint8_t r, g, b, a;
} Color;

typedef void (*OnClickCallback)(Widget v, void *userData);
typedef const char *(*ToStringCallback)(void *item);

/*** util Macros ***/
#define ARRAY_LEN(...) (sizeof(__VA_ARGS__)/sizeof((__VA_ARGS__)[0]))

/*** Widgets (and Wrappers) ***/
Widget xuiCreateButton(const char *text, OnClickCallback callback);
Widget xuiCreateCheckBox(const char *text, bool selected);
// Widget xuiCreateColorPicker();
// Widget xuiCreateDelimiter();
#define DropdownMenu(itemType, toString) xuiCreateDropdownMenu(sizeof(itemType), toString)
Widget xuiCreateDropdownMenu(int itemSize, ToStringCallback callback);
void xuiDropdownMenuAddData(Widget dropdownMenu, void *data, int count);
Widget xuiCreateHyperLink(const char *link);
// Widget xuiCreateImageView(const char *imagePath);
Widget xuiCreateLabel(const char *text);
Widget xuiCreateRadioButton(const char *text, bool selected, int groupId);
Widget xuiCreateSeparator();
Widget xuiCreateSlider(float min, float max, float step);
Widget xuiCreateText(const char *text);
// Widget xuiCreateTextField();
Widget xuiCreateToggleButton(const char *text, bool selected);

/*** Layouts (and Wrappers) ***/
#define LinearLayout(orient, ...) xuiCreateLinearLayout(orient, (Widget[])__VA_ARGS__, ARRAY_LEN((Widget[])__VA_ARGS__))
Widget xuiCreateLinearLayout(Orientation orient, Widget children[], int count);
// Widget xuiCreateListView()
// Widget xuiCreateTableView()
Widget xuiCreateScrollPane(Widget child);
#define SplitPane(orient, ...) xuiCreateSplitPane(orient, (Widget[])__VA_ARGS__, ARRAY_LEN((Widget[])__VA_ARGS__))
Widget xuiCreateSplitPane(Orientation orient, Widget children[], int count);

/*** Special Widget ***/
// Dialog
// Toast
// ToolTip

#endif

#ifndef XUI_H
#define XUI_H

#include <stdbool.h>
#include <stdint.h>

void xuiInit();

/*** Basic for start ***/
typedef struct xuiWidget *Widget;

typedef struct xuiScece *Scene;
#define Scene(widget) xuiCreateScene(widget)
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
	Property_Zindex,
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

#define xuiColor(r, g, b, a) ((Color){(r),(g),(b),(a)})

typedef struct Insets {
	int t, l, b, r;
} Insets;

#define xuiInsets(t, l, b, r) ((Insets){(t),(l),(b),(r)})

typedef void (*OnClickCallback)(Widget v, void *userData);
typedef void (*OnSelectedCallback)(Widget v, bool isSelected, void *userData);
typedef const char *(*ToStringCallback)(void *item);

/*** util Macros ***/
#define ARRAY_LEN(...) (sizeof(__VA_ARGS__)/sizeof((__VA_ARGS__)[0]))

/*** Widgets (and Wrappers) ***/
#define Button(text, callback) xuiCreateButton(text, callback)
Widget xuiCreateButton(const char *text, OnClickCallback callback);
#define CheckBox(text, selected) xuiCreateCheckBox(text, selected)
Widget xuiCreateCheckBox(const char *text, bool selected);
// Widget xuiCreateColorPicker();
// Widget xuiCreateDelimiter();
#define DropdownMenu(itemType, toString) xuiCreateDropdownMenu(sizeof(itemType), toString)
Widget xuiCreateDropdownMenu(int itemSize, ToStringCallback callback);
void xuiDropdownMenuAddData(Widget dropdownMenu, void *dataList, int count);
#define HyperLink(link) xuiCreateText(link)
// Widget xuiCreateHyperLink(const char *link);
// Widget xuiCreateImageView(const char *imagePath);
#define Label(text) xuiCreateLabel(text)
Widget xuiCreateLabel(const char *text);
#define RadioButton(text, selected, groupId) xuiCreateRadioButton(text, selected, groupId)
Widget xuiCreateRadioButton(const char *text, bool selected, int groupId);
#define Separator() xuiCreateSeparator()
// NOTICE: only Horizontal
Widget xuiCreateSeparator();
#define Slider(min, max, step) xuiCreateSlider(min, max, step)
Widget xuiCreateSlider(float min, float max, float step);
float xuiSliderGetValue(Widget slider);
#define Text(text) xuiCreateText(text)
Widget xuiCreateText(const char *text);
// Widget xuiCreateTextField();
#define ToggleButton(text, callback) xuiCreateToggleButton(text, callback)
Widget xuiCreateToggleButton(bool selected, OnSelectedCallback callback);

/*** Layouts (and Wrappers) ***/
#define LinearLayout(orient, ...) xuiCreateLinearLayout(orient, (Widget[])__VA_ARGS__, ARRAY_LEN((Widget[])__VA_ARGS__))
Widget xuiCreateLinearLayout(Orientation orient, Widget children[], int count);
// Widget xuiCreateListView()
// Widget xuiCreateTableView()
#define ScrollPane(child) xuiCreateScrollPane(child)
// NOTICE: only Vertical
Widget xuiCreateScrollPane(Widget child);
#define SplitPane(orient, ...) xuiCreateSplitPane(orient, (Widget[])__VA_ARGS__, ARRAY_LEN((Widget[])__VA_ARGS__))
Widget xuiCreateSplitPane(Orientation orient, Widget children[], int count);

/*** Special Widget ***/
// Dialog
// Toast
// ToolTip

#endif

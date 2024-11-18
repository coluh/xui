#include "../include/xui.h"
#include "../src/util/log.h"
#include <stdbool.h>

void hi(Widget v, void *userData) {
	Log("Hello!");
}

void callback2(Widget v, void *userData) {
	Log("Not me, HIM!");
}

void tg(Widget v, bool isSelected, void *userData) {
	if (isSelected)
		Log("ToggleButton Toggled.");
	else
		Log("ToggleButton Untoggled.");
}

struct MyData {
	char name[16];
	int magor;
	int minor;
};
const char *toStringMyData(void *item) {
	struct MyData *myData = item;
	return myData->name;
}

int main() {

	xuiInit();

	Widget leftPane = LinearLayout(Orientation_Vertical, {
		Label("Hello, XUI!"),
		Separator(),
		LinearLayout(Orientation_Horizontal, {
			Label("Night Mode"),
			ToggleButton(false, tg),
		}),
		Text("This is a description."),
		LinearLayout(Orientation_Horizontal, {
			Label("Detailed Info:"),
			HyperLink("www.example.com"),
		}),
	});
	setProperty(leftPane, Property_Align, Align_Top);

	struct MyData data[4] = {
		{ "Very Old", 1, 7 }, { "Old", 1, 12 },
		{ "Average", 1, 18 }, { "New", 1, 21 },
	};
	Widget dropdownMenu = DropdownMenu(struct MyData, toStringMyData);
	xuiDropdownMenuAddData(dropdownMenu, data, 4);

	Widget rightPane = LinearLayout(Orientation_Vertical, {
		LinearLayout(Orientation_Horizontal, {
			Label("Oh, buttons:"),
			Button("Click me", hi),
			Button("Click him", callback2),
		}),
		CheckBox("CheckBox Enabled", true),
		LinearLayout(Orientation_Horizontal, {
			Label("Look at the Dropdown menu~"),
			dropdownMenu,
		}),
		Text("Choose one of them:"),
		LinearLayout(Orientation_Horizontal, {
			RadioButton("C", 1, 114),
			RadioButton("Java", 0, 114),
			RadioButton("Rust", 0, 114),
		}),
		Text("Slider~~~"),
		Slider(20, 100, 4),
	});
	// Widget rightPaneWrapper = ScrollPane(rightPane);

	// Widget root = SplitPane(Orientation_Horizontal, {
	Widget root = LinearLayout(Orientation_Horizontal, {
		leftPane, rightPane,
	});

	Scene scene = Scene(root);

	xuiSetSceneTitle(scene, "XUI Example");
	xuiStartScene(scene);

	return 0;
}

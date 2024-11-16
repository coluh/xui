#include "../include/xui.h"
#include "../src/util/log.h"
#include <stdbool.h>

void hi(Widget v, void *userData) {
	Log("Hello!");
}

void callback2(Widget v, void *userData) {
	Log("Not me, HIM!");
}

struct MyData {
	char name[8];
	int magor;
	int minor;
};
const char *toStringMyData(void *item) {
	struct MyData *myData = item;
	return myData->name;
}

int main() {

	Widget leftPane = LinearLayout(Orientation_Vertical, {
		xuiCreateLabel("Hello, XUI!"),
		xuiCreateSeparator(),
		xuiCreateToggleButton("Night Mode", false),
		xuiCreateText("This is a description."),
		LinearLayout(Orientation_Horizontal, {
			xuiCreateLabel("Detailed Info:"),
			xuiCreateHyperLink("www.example.com"),
		}),
	});

	struct MyData data[4] = {
		{ "Very Old", 1, 7 }, { "Old", 1, 12 },
		{ "Average", 1, 18 }, { "New", 1, 21 },
	};
	Widget dropdownMenu = DropdownMenu(struct MyData, toStringMyData);
	xuiDropdownMenuAddData(dropdownMenu, data, 4);

	Widget rightPane = LinearLayout(Orientation_Vertical, {
		LinearLayout(Orientation_Horizontal, {
			xuiCreateLabel("Oh, buttons:"),
			xuiCreateButton("Click me", hi),
			xuiCreateButton("Click him", hi),
		}),
		xuiCreateCheckBox("CheckBox Enabled", true),
		LinearLayout(Orientation_Horizontal, {
			xuiCreateLabel("Look at the Dropdown menu~"),
			dropdownMenu,
		}),
		xuiCreateText("Choose one of them:"),
		LinearLayout(Orientation_Horizontal, {
			xuiCreateRadioButton("C", 1, 114),
			xuiCreateRadioButton("Java", 0, 114),
			xuiCreateRadioButton("Rust", 0, 114),
		}),
		xuiCreateText("Slider~~~"),
		xuiCreateSlider(20, 100, 5),
	});
	Widget rightPaneWrapper = xuiCreateScrollPane(rightPane);

	Widget root = SplitPane(Orientation_Horizontal, {
		leftPane, rightPane,
	});

	Scene scene = xuiCreateScene(root);
	xuiSetSceneTitle(scene, "XUI Example");
	xuiStartScene(scene);

	return 0;
}

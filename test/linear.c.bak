#include "../include/xui.h"
#include "../src/util/log.h"

void hi(Widget v, void *userData) {
	Log("Hello!");
}

int main() {

	xuiInit();

	Widget label = Label("label:");
	setProperty(label, Property_FgColor, 127, 0, 255, 255);
	Widget button = Button("Click me", hi);
	setProperty(button, Property_Align, Align_Top);
	setProperty(button, Property_BgColor, 100, 100, 100, 255);
	setProperty(button, Property_Padding, 30);
	Widget hBox = LinearLayout(Orientation_Horizontal, {
		label,
		button,
	});
	setProperty(hBox, Property_Width, 800);
	setProperty(hBox, Property_Arrange, Arrange_SpaceEvenly);

	Widget d2 = Text("Description line 2");
	setProperty(d2, Property_Align, Align_Left);
	Widget d3 = Text("Description 3");
	setProperty(d3, Property_Align, Align_Right);
	Widget vBox = LinearLayout(Orientation_Vertical, {
		Label("Hello"),
		hBox,
		Text("Description"),
		d2,
		d3,
	});
	setProperty(vBox, Property_Width, 1400);
	setProperty(vBox, Property_Height, 800);

	Scene scene = xuiCreateScene(vBox);
	xuiSetSceneTitle(scene, "LinearLayout");
	xuiStartScene(scene);

	return 0;
}

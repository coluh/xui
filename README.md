
feels a bit high level right...

```C
// test/full.c

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
		LinearLayout(Orientation_Horizontal, {
			Text("Slider~~~"),
			Slider(20, 100, 4),
		}),
	});
	// Widget rightPaneWrapper = ScrollPane(rightPane);
	setProperty(rightPane, Property_Align, Align_Left | Align_Right);

	// Widget root = SplitPane(Orientation_Horizontal, {
	Widget root = LinearLayout(Orientation_Horizontal, {
		leftPane, rightPane,
	});

	Scene scene = Scene(root);

	xuiSetSceneTitle(scene, "XUI Example");
	xuiStartScene(scene);

```

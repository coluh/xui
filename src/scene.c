#include "../include/xui.h"
#include "util/alloc.h"

#include <string.h>

struct SceneSt {
	Widget root;
	char *title;
};

Scene xuiCreateScene(Widget widget) {
	Scene scene = callo(1, sizeof(struct SceneSt));
	scene->root = widget;
	return scene;
}

void xuiSetSceneTitle(Scene scene, const char *title) {
	scene->title = strdup(title);
}

void xuiStartScene(Scene scene) {
	;
}

void xuiDestroyScene(Scene scene) {
	if (scene->title)
		free(scene->title);

	//  destroy widget...

	free(scene);
}

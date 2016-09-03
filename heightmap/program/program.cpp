#include <main/main.h>

int Program::onLoad() {
	data = NULL;
	controller = NULL;
	return 0;
}

int Program::onDispose() {
	return 0;
}

int Program::onStart() {
	if (!wnd.open())
		return 1;
	data = new Storage();
	controller = new Controller(&wnd.renderWindow, data);
	return 0;
}

int Program::onStop() {
	delete controller;
	controller = NULL;
	delete data;
	data = NULL;
	wnd.close();
	return 0;
}

int Program::main() {
	bool done(0);
	while (!done) {
		if (wnd.peekMessageAsync(done))
			continue;
		controller->invalidate();
		controller->drawScene();
	}
	return 0;
}

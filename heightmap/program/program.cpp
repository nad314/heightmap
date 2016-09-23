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
	core::Debug::enable();
	if (!wnd.open())
		return 1;
	GL::setVsync(0);
	glExt::init();
	if (glExt::error.count() > 0) {
		core::Debug::print("Error in glExt::init()\n");
		if (core::Debug::isEnabled())
			system("pause");
		return 1; //we hav errors
	}
	data = new Storage();
	controller = new Controller(&wnd.renderWindow, data);
	ShowWindow(wnd, SW_SHOW);
	SetForegroundWindow(wnd);	
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
		controller->drawScene();
		Sleep(5);
	}
	return 0;
}

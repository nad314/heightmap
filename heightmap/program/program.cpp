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
	glClear(GL_COLOR_BUFFER_BIT);
	GL::swapBuffers(wnd.renderWindow);

	wglMakeCurrent(NULL, NULL);
	std::thread t(&Program::load, this);
	t.detach();

	return 0;
}

void Program::load() {
	Controller::lock();
	data->load();
	wnd.load();
	Controller::unlock();
	Controller::invalidate();
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
		if (wnd.peekMessageAsync(done, Controller::busy))
			continue;
		controller->drawScene();
		Sleep(5);
	}
	return 0;
}

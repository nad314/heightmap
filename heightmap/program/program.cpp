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
	Controller::busy = true;
	Controller::get().drawScene();

	printf("Starting thread...\n");
	wglMakeCurrent(NULL, NULL);
	std::thread t([&]{
		GL::makeCurrent(*Controller::get().getParent());
		Controller::busy = true;
		Storage& data = Controller::get().storage();
		data.loadTextureMaterials();
		Sidebar::get().terrainTab.matFrame.makeButtons();
		if (data.textures.count())
			data.material = data.textures[0];
		wglMakeCurrent(NULL, NULL);
		Controller::busy = false;
		Controller::invalidate();
		printf("Thread ended\n");
	});
	t.detach();
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
		if (wnd.peekMessageAsync(done, Controller::busy))
			continue;
		controller->drawScene();
		Sleep(5);
	}
	return 0;
}

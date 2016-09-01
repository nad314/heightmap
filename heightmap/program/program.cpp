#include <main/main.h>

int Program::onLoad() {
	return 0;
}

int Program::onDispose() {
	return 0;
}

int Program::onStart() {
	if (!wnd.open())
		return 1;
	return 0;
}

int Program::onStop() {
	wnd.close();
	return 0;
}

int Program::main() {
	bool done(0);
	while (!done) {
		if (wnd.peekMessage(done)||wnd.renderWindow.peekMessage())
			continue;
		wnd.renderWindow.onPaint(core::eventInfo(NULL, NULL, 0, 0));
		/*
		GL::pushCurrent();
		GL::makeCurrent(wnd.renderWindow);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GL::swapBuffers(wnd.renderWindow);
		GL::popCurrent();
		*/
		Sleep(1);
	}
	return 0;
}

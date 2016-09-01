#include <main\main.h>

void RenderWindow::onOpening() {
	Window::onOpening();
	setTitle("Render Form");
	setClass("RenderForm");
	setStyle(WS_CHILD | WS_VISIBLE);
	setFlags(0);
	setSize(240, 120); //bandaid
}

void RenderWindow::onOpened() {
	Window::onOpened();
	if (width == 0 || height == 0)
		return;
	GL::createContext(*this);
	GL::init(*this);
	GL::setVsync(0);
}

void RenderWindow::onClosing() {
	GL::deleteContext();
	Window::onClosing();
}

int RenderWindow::onPaint(const core::eventInfo& e) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GL::swapBuffers(*this);
	return e;
}

int RenderWindow::onResize(const core::eventInfo& e) {
	GL::init(*this);
	return Window::onResize(e);
}

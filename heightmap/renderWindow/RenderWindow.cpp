#include <main\main.h>

void RenderWindow::onOpening() {
	Window::onOpening();
	setTitle("Render Form");
	setStyle(WS_CHILD | WS_VISIBLE);
	setFlags(0);
}
 
void RenderWindow::onOpened() {
	Window::onOpened();
	if (width == 0 || height == 0)
		return;
	GL::createContext(*this);
	GL::init(*this);
}

void RenderWindow::onClosing() {
	GL::deleteContext();
	Window::onClosing();
}

int RenderWindow::onResize(const core::eventInfo& e) {
	Window::onResize(e);
	GL::ortho(*this);
	return e;
}

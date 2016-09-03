#include <main\main.h>

bool Controller::repaint = 0;

Controller::Controller(core::Window* ptr, Storage* storage) {
	parent = ptr;
	parent->attach(this);
	data = storage;
	invalidate();
}

Controller::~Controller() {
	if (parent)
		parent->detach();
	data = NULL;
}

int Controller::onPaint(const core::eventInfo& e) {
	drawScene();
	return EventListener::onPaint(e);
}

void Controller::drawScene() {
	if (!parent||!repaint)
		return;
	glClearColor(0.1f, 0.1f, 0.11f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GL::swapBuffers(*parent);
	repaint = 0;
}

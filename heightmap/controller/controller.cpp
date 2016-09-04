#include <main\main.h>

bool Controller::repaint = 0;

Controller::Controller(core::Window* ptr, Storage* storage) {
	parent = ptr;
	parent->attach(this);
	data = storage;
	invalidate();

	core::Window* mw = dynamic_cast<core::Window*>(parent->getParent());
	
	if (data->img.width > 20 && data->img.height > 20 && mw) {
		core::Monitor::Enumerate();
		mw->resize(data->img.width + 16, data->img.height + 32);
		mw->centerToMonitor(core::Monitor::MonitorFromId(1));
	}
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GL::drawImage(data->img);
	GL::swapBuffers(*parent);
	repaint = 0;
}

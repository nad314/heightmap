#include <main/main.h>

int Controller::onResize(const core::eventInfo& e) {
	if (busy)return e;
	EventListener::onResize(e);
	lpdata->view.perspective(*parent, 41.5f, 0.1f, 100.0f);
	invalidate();
	return e;
}

int Controller::onLButtonDown(const core::eventInfo& e) {
	if (busy) return e;
	SetCapture(*parent);
	if (tool) tool->onLButtonDown(e);
	return EventListener::onLButtonDown(e);
}

int Controller::onLButtonUp(const core::eventInfo& e) {
	if (busy) return e;
	ReleaseCapture();
	if (tool) tool->onLButtonUp(e);
	return EventListener::onLButtonUp(e);
}

int Controller::onRButtonDown(const core::eventInfo& e) {
	if (busy) return e;
	dragging = 1;
	SetCapture(*parent);
	return EventListener::onLButtonDown(e);
}

int Controller::onRButtonUp(const core::eventInfo& e) {
	if (busy) return e;
	dragging = 0;
	ReleaseCapture();
	return EventListener::onLButtonUp(e);
}


int Controller::onMouseMove(const core::eventInfo& e) {
	if (busy)return e;
	core::vec2i lpos = mpos;
	mpos = core::vec2i(LOWORD(e.lP), HIWORD(e.lP));
	if (tool) tool->onMouseMove(e);
	if (dragging) {
		core::matrixf rot;
		rot.rotate(0.25f*(mpos.x - lpos.x), 0.0f, 1.0f, 0.0f);
		rot.rotate(0.25f*(mpos.y - lpos.y), 1.0f, 0.0f, 0.0f);
		rotation = rotation*rot;
		lpdata->view.modelview = rotation*translation;
		invalidate();
	}
	invalidate(); //remove after debug state

	return EventListener::onMouseMove(e);
}


int Controller::onPaint(const core::eventInfo& e) {
	drawScene();
	return EventListener::onPaint(e);
}

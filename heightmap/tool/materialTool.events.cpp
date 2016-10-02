#include <main/main.h>

int MaterialTool::onPaint(const core::eventInfo& e) {
	if (traced) drawBrush(position);
	return 0;
}

int MaterialTool::onLButtonDown(const core::eventInfo& e) {
	lpos = mpos;
	drawing = raytrace(lastPoint);
	return 0;
}

int MaterialTool::onLButtonUp(const core::eventInfo& e) {
	drawing = 0;
	return 0;
}

int MaterialTool::onMouseMove(const core::eventInfo& e) {
	Controller::invalidate();
	mpos = core::vec2i(LOWORD(e.lP), HIWORD(e.lP));
	traced = raytrace(position);
	if (!drawing) return 0;
	Storage& data = Controller::get().storage();
	if (!traced || (position - lastPoint).length() < brush.step*brush.metrics.x)
		return 0;
	lastPoint = position;
	sendCompute(position);
	return 0;
}

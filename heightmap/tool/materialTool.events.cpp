#include <main/main.h>

int MaterialTool::onPaint(const core::eventInfo& e) {
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
	mpos = core::vec2i(LOWORD(e.lP), HIWORD(e.lP));
	if (!drawing) return 0;
	Storage& data = Controller::get().storage();
	vec3 point;
	if (!raytrace(point) || (point - lastPoint).length() < 0.25f)
		return 0;
	lastPoint = point;
	sendCompute(point);
	return 0;
}

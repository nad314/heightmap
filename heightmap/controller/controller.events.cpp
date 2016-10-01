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
	dragging = 1;
	SetCapture(*parent);
	return EventListener::onLButtonDown(e);
}

int Controller::onLButtonUp(const core::eventInfo& e) {
	if (busy) return e;
	dragging = 0;
	ReleaseCapture();
	return EventListener::onLButtonUp(e);
}

int Controller::onMouseMove(const core::eventInfo& e) {
	if (busy)return e;
	core::vec2i lpos = mpos;
	mpos = core::vec2i(LOWORD(e.lP), HIWORD(e.lP));
	if (dragging) {
		core::matrixf rot;
		rot.rotate(0.25f*(mpos.x - lpos.x), 0.0f, 1.0f, 0.0f);
		rot.rotate(0.25f*(mpos.y - lpos.y), 1.0f, 0.0f, 0.0f);
		rotation = rotation*rot;
		lpdata->view.modelview = rotation*translation;
		invalidate();
	}
	invalidate(); //remove after debug state


	Storage& data = *lpdata;
	matrixf invmat = data.view.modelview*data.view.projection;
	invmat.invert();
	vec4 r0 = invmat*data.view.unproject(vec4((float)mpos.x, (float)parent->height - mpos.y, 0.0f, 1.0f), *parent);
	r0 /= r0.w;
	vec4 r1 = invmat*data.view.unproject(vec4((float)mpos.x, (float)parent->height - mpos.y, 1.0f, 1.0f), *parent);
	r1 /= r1.w;
	r1 = (r1 - r0).normalize3d();
	float t = core::Math::rayPlaneT(r0.xyz(), r1.xyz(), vec4(0, 1, 0, 0));
	if (t >= 0.0f)
		core::Debug::print("yes");
	else core::Debug::print("no");

	vec3 point = r0.xyz() + r1.xyz()*t;
	data.sendCompute(point);


	return EventListener::onMouseMove(e);
}


int Controller::onPaint(const core::eventInfo& e) {
	drawScene();
	return EventListener::onPaint(e);
}

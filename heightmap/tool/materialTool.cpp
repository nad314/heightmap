#include <main/main.h>

MaterialTool* core::Getter<MaterialTool>::getter = NULL;

MaterialTool::MaterialTool() {
	core::Path::pushDir();
	core::Path::goHome();
	core::Path::cd("../data/");
	if (!compute.load("shaders/compute/drawTexture.glsl"))
		core::Debug::error("Could not load compute shader\n");
	else compute.printDebugInfo();
	core::Path::popDir();

	compute.start();
	uniform[0] = glExt::getUniformLocation(compute, "cursor");
	uniform[7] = glExt::getUniformLocation(compute, "brush");
	uniform[1] = glExt::getUniformLocation(compute, "rect");
	uniform[2] = glExt::getUniformLocation(compute, "texSize");
	uniform[4] = glExt::getUniformLocation(compute, "chunkPos");

	uniform[5] = glExt::getUniformLocation(compute, "matDiffuse");
	uniform[6] = glExt::getUniformLocation(compute, "matNormal");
	uniform[3] = glExt::getUniformLocation(compute, "matScale");
	compute.stop();
}

MaterialTool::~MaterialTool() {}

int MaterialTool::onPaint(const core::eventInfo& e) {
	return 0;
}

int MaterialTool::onLButtonDown(const core::eventInfo& e) {
	lpos = mpos;
	drawing = 1;
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
	matrixf invmat = data.view.modelview*data.view.projection;
	invmat.invert();
	vec4 r0 = invmat*data.view.unproject(vec4((float)mpos.x, (float)Controller::get().getParent()->height - mpos.y, 0.0f, 1.0f), *Controller::get().getParent());
	r0 /= r0.w;
	vec4 r1 = invmat*data.view.unproject(vec4((float)mpos.x, (float)Controller::get().getParent()->height - mpos.y, 1.0f, 1.0f), *Controller::get().getParent());
	r1 /= r1.w;
	r1 = (r1 - r0).normalize3d();
	float t = core::Math::rayPlaneT(r0.xyz(), r1.xyz(), vec4(0, 1, 0, 0));
	if (t < 0.0f) return 0;

	vec3 point = r0.xyz() + r1.xyz()*t;
	data.sendCompute(point);
	return 0;
}


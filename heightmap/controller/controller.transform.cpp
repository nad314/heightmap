#include <main/main.h>

void Controller::initViewMatrix() {
	Storage& data = storage();
	lpdata->view.perspective(*parent, 41.5f, 0.1f, 100.0f);
	rotation.init();
	rotation.rotate(45.0f, 1.0f, 0.0f, 0.0f);
	rotation.rotate(-30.0f, 0.0f, 1.0f, 0.0f);
	translation.init();
	translation.translate(0.0f, 0.0f, -2.0f);
	pan.init();
	if (data.map.mesh.count()) {
		vec4 min, max;
		min = max = data.map.mesh[0].rect;
		for (auto& i : data.map.mesh) {
			min = min.min(i.rect);
			max = max.max(i.rect);
		}
		vec2 pos = vec2(min.x + max.z, min.y + max.w)*0.5f;
		pan.translate(-pos.x, 0.0f, -pos.y);
	}
	updateViewMatrix();
}

void Controller::updateViewMatrix() {
	lpdata->view.modelview = pan*rotation*translation;
}


bool Controller::raytrace(vec3& point, const vec2i& mp) {
	Storage& data = storage();
	matrixf invmat = data.view.modelview*data.view.projection;
	invmat.invert();
	vec4 r0 = invmat*data.view.unproject(vec4((float)mp.x, (float)Controller::get().getParent()->height - mp.y, 0.0f, 1.0f), *Controller::get().getParent());
	r0 /= r0.w;
	vec4 r1 = invmat*data.view.unproject(vec4((float)mp.x, (float)Controller::get().getParent()->height - mp.y, 1.0f, 1.0f), *Controller::get().getParent());
	r1 /= r1.w;
	r1 = (r1 - r0).normalize3d();
	float t = core::Math::rayPlaneT(r0.xyz(), r1.xyz(), vec4(0, 1, 0, 0));
	if (t < 0.0f) return 0;
	point = r0.xyz() + r1.xyz()*t;
	return 1;
}

bool Controller::brushRectIntersection(const vec3& pos, const float& rad, const vec4& rect) {
	if (pos.x + rad < rect.x) return 0;
	if (pos.x - rad > rect.z) return 0;
	if (pos.z + rad < rect.w) return 0;
	if (pos.z - rad > rect.y) return 0;
	return 1;
}
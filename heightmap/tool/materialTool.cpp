#include <main/main.h>

MaterialTool* core::Getter<MaterialTool>::getter = NULL;

MaterialTool::MaterialTool() {
	core::Path::pushDir();
	core::Path::goHome();
	core::Path::cd("../data/");
	if (!compute.load("shaders/compute/drawTexture.glsl"))
		core::Debug::error("Could not load compute shader\n");
	else compute.printDebugInfo();
	if (!brushDisplay.load("shaders/brushDisplay/vertex.glsl", "shaders/brushDisplay/fragment.glsl", "fragColor"))
		core::Debug::error("Could not load brushDisplay shader\n");
	else brushDisplay.printDebugInfo();
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

	brushDisplay.start();
	brushAttrib[0] = glExt::getAttribLocation(brushDisplay, "pos");
	brushUniform[0] = glExt::getUniformLocation(brushDisplay, "view");
	brushUniform[1] = glExt::getUniformLocation(brushDisplay, "proj");
	brushUniform[2] = glExt::getUniformLocation(brushDisplay, "s");
	brushUniform[3] = glExt::getUniformLocation(brushDisplay, "r");
	brushDisplay.stop();
}

MaterialTool::~MaterialTool() {}


bool MaterialTool::raytrace(vec3& point) {
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
	point = r0.xyz() + r1.xyz()*t;
	return 1;
}

MaterialTool& MaterialTool::sendCompute(const vec3& point) {
	vec2 imageSize = vec2(512);
	vec4 rect = vec4(-1, 1, 1, -1);
	Storage& data = Controller::get().storage();

	glExt::memoryBarrier(GL_ALL_BARRIER_BITS);
	compute.start();
	glExt::uniform2fv(uniform[0], 1, vec2(point.x, point.z));
	glExt::uniform2fv(uniform[7], 1, brush.metrics);
	glExt::uniform4fv(uniform[1], 1, rect);
	glExt::uniform2fv(uniform[2], 1, imageSize);
	glExt::uniform2fv(uniform[4], 1, data.chunk.pos);

	glExt::uniform1i(uniform[5], 0);
	glExt::uniform1i(uniform[6], 1);
	glExt::uniform2fv(uniform[3], 1, data.material.scale);
	data.material.diffuse.bind(0);
	data.material.normal.bind(1);

	glExt::bindImageTexture(1, data.chunk.material.diffuse, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA8);
	glExt::bindImageTexture(2, data.chunk.material.normal, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA8);
	glExt::dispatchCompute((int)imageSize.x / 16, (int)imageSize.y / 16, 1);
	compute.stop();
	glExt::memoryBarrier(GL_ALL_BARRIER_BITS);
	return *this;
}

MaterialTool& MaterialTool::drawBrush(const vec3& point){
	static vec3 quad[4];

	float radius = brush.metrics.x;
	quad[0] = point + vec3(-radius, 0.0f, radius);
	quad[1] = point + vec3(radius, 0.0f, radius);
	quad[2] = point + vec3(radius, 0.0f, -radius);
	quad[3] = point + vec3(-radius, 0.0f, -radius);

	Storage& data = Controller::get().storage();
	brushDisplay.start();
	data.view.sendTo(brushDisplay, brushUniform[0], brushUniform[1]);
	glExt::uniform3fv(brushUniform[2], 1, const_cast<GLfloat*>(&point.x)); //position
	glExt::uniform1f(brushUniform[3], radius);

	glExt::bindVertexArray(0);
	glExt::bindBuffer(GL_ARRAY_BUFFER,  0);
	glExt::enableVertexAttribArray(brushAttrib[0]);
	glExt::vertexAttribPointer(brushAttrib[0], 3, GL_FLOAT, false, 0, quad);
	glDrawArrays(GL_QUADS, 0, 4);
	brushDisplay.stop();
	return *this;
}

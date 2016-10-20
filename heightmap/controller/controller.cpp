#include <main\main.h>

Controller* core::Getter<Controller>::getter = NULL;
bool Controller::busy = 0;
bool Controller::repaint = 0;

Controller::Controller(core::Window* ptr, Storage* storage) {
	set(*this);
	parent = ptr;
	parent->attach(this);
	lpdata = storage;
	invalidate();

	core::Window* mw = dynamic_cast<core::Window*>(parent->getParent());
	core::Monitor::Enumerate();
	mw->centerToMonitor(core::Monitor::MonitorFromId(1));

	initGL();
	initViewMatrix();

	tool = new MaterialTool;
}

Controller::~Controller() {
	if (parent)
		parent->detach();
	lpdata = NULL;
	delete tool;
}

void Controller::drawScene(const core::eventInfo& e) {
	if (!parent||!repaint)
		return;
	if (busy) {
		isbusy = 1;
		return;
	}
	else if (isbusy) {
		isbusy = 0;
		GL::makeCurrent(*parent);
	}
	Storage& data = *lpdata;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	data.shader.start();
	glExt::activeTexture(GL_TEXTURE0);
	data.chunk.material.diffuse.bind();
	glExt::activeTexture(GL_TEXTURE1);
	data.chunk.material.normal.bind();
	data.view.sendTo(data.shader, "modelview", "projection");
	glExt::uniform1i(glExt::getUniformLocation(data.shader, "diffuseMap"), 0);
	glExt::uniform1i(glExt::getUniformLocation(data.shader, "normalMap"), 1);
	glExt::uniform1f(glExt::getUniformLocation(data.shader, "scale"), data.chunk.material.scale.x);
	//data.model.drawTris();
	//data.chunk.draw();
	vec3 a, b;
	int counter = 0;
	for (auto& i : data.map.mesh) {
		i.material.diffuse.bind(0);
		i.material.normal.bind(1);
		glExt::uniform1f(glExt::getUniformLocation(data.shader, "scale"), i.material.scale.x);
		a = vec3(i.rect.x, -0.2f, i.rect.y);
		b = vec3(i.rect.z, 0.2f, i.rect.w);
		if (data.frustum.aabbIntersection(a, b)) {
			i.draw();
			++counter;
		}
	}
	data.shader.stop();
	core::glTexture::unbind();
	glDisable(GL_DEPTH_TEST);

	if (tool) tool->onPaint(e);

	GL::swapBuffers(*parent);
	repaint = 0;
}

void Controller::initGL() {
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE0);
	glEnable(GL_TEXTURE1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	glClearColor(0.1f, 0.1f, 0.11f, 1.0f);
}

void Controller::clearTextures() {
	if (!lpdata) return;
	Storage& data = *lpdata;
	core::Image img;
	img.make(128, 128, 32);
	core::Core2D::clearImage(img, core::Color(255));
	data.material.diffuse.make(img);
	core::Core2D::clearImage(img, core::Color(128, 128, 255, 255));
	data.material.normal.make(img);
}

void Controller::makeImage(core::glTexture& texture, core::Image& image) {
	texture.dispose();
	texture.make(image);
	texture.genMipmaps();
}

void Controller::lock() {
	busy = 1;
	GL::makeCurrent(*get().parent);
}

void Controller::unlock() {
	wglMakeCurrent(NULL, NULL);
	busy = 0;
}



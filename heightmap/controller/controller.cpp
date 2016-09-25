#include <main\main.h>

Controller* Controller::defController = NULL;
bool Controller::busy = 0;
bool Controller::repaint = 0;

Controller::Controller(core::Window* ptr, Storage* storage) {
	defController = this;
	parent = ptr;
	parent->attach(this);
	lpdata = storage;
	invalidate();

	core::Window* mw = dynamic_cast<core::Window*>(parent->getParent());
	core::Monitor::Enumerate();
	mw->centerToMonitor(core::Monitor::MonitorFromId(1));

	initGL();
	rotation.init();
	rotation.rotate(15.0f, 1.0f, 0.0f, 0.0f);
	rotation.rotate(-20.0f, 0.0f, 1.0f, 0.0f);
	translation.init();
	translation.translate(0.0f, 0.0f, -6.0f);
	lpdata->view.perspective(*parent, 41.5f, 0.1f, 100.0f);
	lpdata->view.modelview = rotation*translation;
}

Controller::~Controller() {
	if (parent)
		parent->detach();
	lpdata = NULL;
}

void Controller::drawScene() {
	if (!parent||!repaint)
		return;
	if (busy) {
		if (!isbusy) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			GL::swapBuffers(*parent);
			repaint = 0;
		}
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
	data.material.diffuse.bind();
	glExt::activeTexture(GL_TEXTURE1);
	data.material.normal.bind();
	data.view.sendTo(data.shader, "modelview", "projection");
	glExt::uniform1i(glExt::getUniformLocation(data.shader, "diffuseMap"), 0);
	glExt::uniform1i(glExt::getUniformLocation(data.shader, "normalMap"), 1);
	glExt::uniform1f(glExt::getUniformLocation(data.shader, "scale"), data.material.scale.x);
	data.model.drawTris();
	data.shader.stop();
	core::glTexture::unbind();
	glDisable(GL_DEPTH_TEST);
	GL::swapBuffers(*parent);
	repaint = 0;
}

void Controller::initGL() {
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE0);
	glEnable(GL_TEXTURE1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

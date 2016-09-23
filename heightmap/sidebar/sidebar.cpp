#include <main/main.h>

void Sidebar::onOpening() {
	Frame::onOpening();
	setSize(256, 256);
	setStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	setClass("MaterialPreviewSidebar");
}

void Sidebar::onOpened() {
	Frame::onOpened();
	setBackColor(App::Theme::FormBackColor);
	
	matFrame.setParent(this);
	matFrame.open();
	push(&matFrame);
	MoveWindow(matFrame, 2, 2, App::Theme::sidebarWidth - 12, 258, true);

	push(clearButton.make(nextVertical() + core::vec4i(2, 2, App::Theme::sidebarWidth - 10, 24), "Clear All", *this, [](core::Form& f)->void {
		Sidebar& p = dynamic_cast<Sidebar&>(f);
		if (!p) return;
		Controller::get().clearTextures();
		Controller::get().invalidate();
		p.invalidate();
		core::Debug::print("Cleared Images\n");
	}));

	push(sizeSlider.make(nextVertical() + core::vec4i(2, 2, App::Theme::sidebarWidth - 10, 22), 1, *this, [](float pos, core::Form& f)->void {
		float scale = pow(0.5f, (0.5f - pos) * 2);
		Storage& data = Controller::get().storage();
		data.material.scale = core::vec2(scale, scale);
		Controller::invalidate();
		core::Debug::print("Texture Scale: %.2f\n", scale);
	}));

	push(saveButton.make(nextVertical() + core::vec4i(2, 2, App::Theme::sidebarWidth - 10, 22), "Save Material", *this, [](core::Form& f)->void {
		core::Path::pushDir();
		std::string path = core::Path::getSaveFileName("Materials (.mat)\0*.mat\0\0");
		path = core::Path::pushExt("mat", path);
		core::Path::popDir();
		if (!Controller::get().storage().material.save(path.c_str(), core::Path::getHomeDir().c_str()))
			core::Debug::print("Error occured while trying to save material\n");
	}));

	push(loadButton.make(nextVertical() + core::vec4i(2, 2, App::Theme::sidebarWidth - 10, 22), "Open Material", *this, [](core::Form& f)->void {
		core::Path::pushDir();
		std::string path = core::Path::getOpenFileName("Materials (.mat)\0*.mat\0\0");
		core::Path::popDir();
		Storage& data = Controller::get().storage();
		if (!data.material.load(path.c_str(), core::Path::getHomeDir().c_str()))
			core::Debug::print("Error occured while trying to open material\n");
		data.material.genMipmaps();
		Controller::get().invalidate();
		Sidebar& p = dynamic_cast<Sidebar&>(f);
		if (!p) return;
	}));


	setControlColors();
}

void Sidebar::onEndPaint(const core::eventInfo& e) {
	Frame::onEndPaint(e);
}


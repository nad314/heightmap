#include <main/main.h>

Sidebar* core::Getter<Sidebar>::getter = NULL;

void Sidebar::onOpening() {
	Frame::onOpening();
	setSize(256, 256);
	setStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
}

void Sidebar::onOpened() {
	Frame::onOpened();
	setBackColor(App::Theme::FormBackColor);
	push(tabSwitcher.make(vec4i(4, 2, App::Theme::sidebarClientWidth-4, 22), "Terrain", *this));
	terrainTab.setParent(this).open();
	push(&terrainTab);
	setControlColors();
}

void Sidebar::onClosing() {
	Frame::onClosing();
	terrainTab.close();
}

int Sidebar::onLButtonDown(const core::eventInfo& e) {
	if (Controller::get().busy)
		return e;
	return Frame::onLButtonDown(e);
}

int Sidebar::onLButtonUp(const core::eventInfo& e) {
	if (Controller::get().busy)
		return e;
	return Frame::onLButtonUp(e);
}

int Sidebar::onResize(const core::eventInfo& e) {
	Frame::onResize(e);
	Rect fullRect = getClientRect() + Rect(0, 24, 0, 0);
	terrainTab.move(fullRect);
	return 0;
}

void Sidebar::load() {
	terrainTab.load();
}
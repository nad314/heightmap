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
	push(tabSwitcher.make(vec4i(4, 2, App::Theme::sidebarClientWidth - 4, 22), "Terrain", *this, [](core::Control& c, Form& f)->void {
		try {
			Sidebar& sb = dynamic_cast<Sidebar&>(f);
			Rect r = sb.getRect() + Rect(c.rect.x, c.rect.w, 0, 0);
			sb.tabMenu.show().moveTo(vec2i(r.x, r.y));
		}
		catch (std::bad_cast e) { core::Debug::log("%s\n", e.what()); }
	}));
	terrainTab.setParent(this).open();
	push(&terrainTab);

	tabMenu.setParent(this);
	core::Theme::setFormColor(tabMenu);
	tabMenu.controlBorderColor = tabMenu.controlBackColor;
	tabMenu.push((new core::Button())->make(tabMenu.nextVertical() + Rect(0, 0, 200, 20), "Texture", tabMenu, [](core::Control& c, core::Form& f)->void {
		try {
			core::DropdownMenu& dm = dynamic_cast<core::DropdownMenu&>(f);
			Sidebar::get().tabSwitcher.setText("Texture");
			Sidebar::get().invalidate();
			Sidebar::get().__invalidate();
			dm.hide();
		}
		catch (std::bad_cast e) { core::Debug::log("%s\n", e.what()); }
	}));
	tabMenu.push((new core::Button())->make(tabMenu.nextVertical() + Rect(0, 0, 200, 20), "Terrain", tabMenu, [](core::Control& c, core::Form& f)->void {
		try {
			core::DropdownMenu& dm = dynamic_cast<core::DropdownMenu&>(f);
			Sidebar::get().tabSwitcher.setText("Terrain");
			Sidebar::get().invalidate();
			Sidebar::get().__invalidate();
			dm.hide();
		}
		catch (std::bad_cast e) { core::Debug::log("%s\n", e.what()); }
	}));

	setControlColors();
}

void Sidebar::onClosing() {
	Frame::onClosing();
	terrainTab.close();
	tabMenu.close();
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
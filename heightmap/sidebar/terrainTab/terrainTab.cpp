#include <main/main.h>

void TerrainTab::onOpening() {
	Frame::onOpening();
	setSize(256, 256);
	setStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
}

void TerrainTab::onOpened() {
	Frame::onOpened();
	setBackColor(App::Theme::FormBackColor);

	const int sbw = App::Theme::sidebarWidth - 10;
	push(matLabel.make(vec4i(2, 2, sbw, 20), "Draw Texture: ", *this));
	Rect next = nextVertical();

	matFrame.setParent(this);
	matFrame.open();
	push(&matFrame);
	matFrame.move(next + vec4i(2, 2, sbw, 192));

	setControlColors();
}

int TerrainTab::onLButtonDown(const core::eventInfo& e) {
	if (Controller::get().busy)
		return e;
	return Frame::onLButtonDown(e);
}

int TerrainTab::onLButtonUp(const core::eventInfo& e) {
	if (Controller::get().busy)
		return e;
	return Frame::onLButtonUp(e);
}

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
	MoveWindow(matFrame, 2, 24, App::Theme::sidebarWidth - 12, 258, true);

	setControlColors();
}

void Sidebar::onEndPaint(const core::eventInfo& e) {
	Frame::onEndPaint(e);
}


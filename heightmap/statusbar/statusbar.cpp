#include <main/main.h>

void Statusbar::onOpening() {
	Form::onOpening();
	setSize(256, 256);
	setStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	setBackColor(core::Theme::controlBackColor);
	setControlColors();
	setClass("MaterialPreviewStatusbar");
	memset(text, 0, 256);
}

void Statusbar::onOpened() {
	Form::onOpened();
	setBackColor(App::Theme::FormBackColor);
}

void Statusbar::onStartPaint(const core::eventInfo& e) {
	__invalidate();
	Form::onStartPaint(e);
}

void Statusbar::onEndPaint(const core::eventInfo& e) {
	Form::onEndPaint(e);
	core::Font::get().print(text, *this, 4, 4);
}

void Statusbar::print(const char* s) {
	strcpy(text, s);
	int n = strlen(text);
	for (int i = 0; i < n; ++i)
		if (text[i] == '\n')
			text[i] = ' ';
	invalidate();
}

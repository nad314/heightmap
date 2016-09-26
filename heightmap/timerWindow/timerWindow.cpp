#include <main/main.h>

TimerWindow* core::Getter<TimerWindow>::getter = NULL;

void TimerWindow::onOpening() {
	Form::onOpening();
	set(*this);
	setStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
}

void TimerWindow::onOpened() {
	Form::onOpened();
	setBackColor(App::Theme::FormBackColor);
	push(daySlider.make(vec4i(0, 0, 10, 10), 0, *this, [](float pos, core::Control& c, core::Form& f)->void {}));
	push(yearSlider.make(vec4i(0, 10, 10, 20), 0, *this, [](float pos, core::Control& c, core::Form& f)->void {}));
	push(dayLabel.make(vec4i(0, 0, 10, 10), "Time of Day:", *this).setAlign(0).setColor(core::Theme::constrastBorderColor));
	push(yearLabel.make(vec4i(0, 0, 10, 10), "Time of Year:", *this).setAlign(0).setColor(core::Theme::constrastBorderColor));
	setControlColors();
}

void TimerWindow::onClosing() {
	Form::onClosing();
}

void TimerWindow::onEndPaint(const core::eventInfo& e) {
	Form::onEndPaint(e);
	core::Core2D::drawRect(getClientRect(), core::Theme::controlBorderColor, *this);
}

int TimerWindow::onResize(const core::eventInfo& e) {
	Form::onResize(e);
	const int labelWidth = 92;
	daySlider.move(vec4i(labelWidth + 2, 2, width-2, 22));
	yearSlider.move(vec4i(labelWidth + 2, 23, width - 2, 43));
	dayLabel.move(vec4i(4, 2, labelWidth, 22));
	yearLabel.move(vec4i(4, 23, labelWidth, 43));
	return 0;
}

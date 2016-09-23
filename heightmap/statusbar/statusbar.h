#pragma once

class Statusbar final : public core::Form, public core::Debugger {
protected:
	char text[256];
public:
	Statusbar() :Form(), Debugger() { core::Debug::attach(this); }
	void onOpening() override;
	void onOpened() override;

	void onStartPaint(const core::eventInfo& e) override;
	void onEndPaint(const core::eventInfo& e) override;
	void print(const char* s) override;
};

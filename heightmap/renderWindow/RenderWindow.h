#pragma once

class RenderWindow : public core::Window {
public:
	void onOpening() override;
	void onOpened() override;
	void onClosing() override;

	int onPaint(const core::eventInfo& e) override;
	int onResize(const core::eventInfo& e) override;
};
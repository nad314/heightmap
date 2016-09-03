#pragma once

class RenderWindow : public core::Window {
public:
	void onOpening() override;
	void onOpened() override;
	void onClosing() override;

	int onResize(const core::eventInfo& e) override;
};
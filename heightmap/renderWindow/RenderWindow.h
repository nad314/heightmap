#pragma once

class RenderWindow final: public core::Window {
protected:
public:
	void onOpening() override;
	void onOpened() override;
	void onClosing() override;

	int onResize(const core::eventInfo& e) override;
};

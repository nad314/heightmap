#pragma once
#include "materialFrame/materialFrame.h"

class Sidebar final : public core::Frame {
private:
	static Sidebar* currentSidebar;
public:
	Sidebar() :Frame() { currentSidebar = this; }
	core::Label matLabel;
	MaterialFrame matFrame;

	char difPath[256];
	char norPath[256];

	void onOpening() override;
	void onOpened() override;
	static void adjustImage(core::Image& source, const core::Image& dest, const int& size);

	void onEndPaint(const core::eventInfo& e) override;
	int onLButtonDown(const core::eventInfo& e) override;
	int onLButtonUp(const core::eventInfo& e) override;
	inline static Sidebar& get() { return *currentSidebar; }
};

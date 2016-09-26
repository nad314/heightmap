#pragma once
#include "terrainTab/terrainTab.h"

class Sidebar final : public core::Frame {
private:
	static Sidebar* currentSidebar;
public:
	core::Button tabSwitcher;
	TerrainTab terrainTab;
	Sidebar() :Frame() { currentSidebar = this; }

	void onOpening() override;
	void onOpened() override;
	void onClosing() override;
	static void adjustImage(core::Image& source, const core::Image& dest, const int& size);

	int onLButtonDown(const core::eventInfo& e) override;
	int onLButtonUp(const core::eventInfo& e) override;
	int onResize(const core::eventInfo& e) override;
	inline static Sidebar& get() { return *currentSidebar; }
};

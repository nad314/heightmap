#pragma once
#include "terrainTab/terrainTab.h"

class Sidebar final : public core::Frame, public core::Getter<Sidebar> {
public:
	core::Button tabSwitcher;
	core::DropdownMenu tabMenu;
	TerrainTab terrainTab;
	Sidebar() :Frame() { set(*this); }

	void onOpening() override;
	void onOpened() override;
	void onClosing() override;
	static void adjustImage(core::Image& source, const core::Image& dest, const int& size);

	int onLButtonDown(const core::eventInfo& e) override;
	int onLButtonUp(const core::eventInfo& e) override;
	int onResize(const core::eventInfo& e) override;
	void load();
};

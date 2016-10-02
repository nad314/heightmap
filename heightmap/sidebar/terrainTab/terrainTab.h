#pragma once
#include "materialFrame/materialFrame.h"

class TerrainTab : public core::Frame  {
public:
	core::ImageButton matButton;
	core::Label matLabel;
	core::Label brushLabel[4];
	core::Slider brushSlider[4];
	MaterialFrame matFrame;

	void onOpening() override;
	void onOpened() override;
	int onLButtonDown(const core::eventInfo& e) override;
	int onLButtonUp(const core::eventInfo& e) override;

	void load();
	void adjustSliders();

};


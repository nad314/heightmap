#pragma once
#include "materialFrame/materialFrame.h"

class TerrainTab : public core::Frame  {
public:
	core::Label matLabel;
	MaterialFrame matFrame;

	void onOpening() override;
	void onOpened() override;
	int onLButtonDown(const core::eventInfo& e) override;
	int onLButtonUp(const core::eventInfo& e) override;

	void load();

};


#pragma once
#include "materialFrame/materialFrame.h"

class Sidebar final : public core::Frame {
public:
	MaterialFrame matFrame;

	core::Button clearButton;
	core::Slider sizeSlider;
	core::Button saveButton;
	core::Button loadButton;

	char difPath[256];
	char norPath[256];

	void onOpening() override;
	void onOpened() override;
	static void adjustImage(core::Image& source, const core::Image& dest, const int& size);

	void onEndPaint(const core::eventInfo& e) override;
};

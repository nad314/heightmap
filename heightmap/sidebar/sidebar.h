#pragma once
#include "materialFrame/materialFrame.h"

class Sidebar final : public core::Frame {
public:
	core::Label matFrameLabel;
	MaterialFrame matFrame;

	char difPath[256];
	char norPath[256];

	void onOpening() override;
	void onOpened() override;
	static void adjustImage(core::Image& source, const core::Image& dest, const int& size);

	void onEndPaint(const core::eventInfo& e) override;
};

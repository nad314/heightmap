#pragma once

class MaterialFrame : public core::Frame {
public:
	core::buffer<core::Image*> image;
	core::buffer<core::ImageButton*> button;

	void onOpening() override;
	void onOpened() override;
	void onClosed() override;
	void onEndPaint(const core::eventInfo& e) override;	
	void makeButtons();
};
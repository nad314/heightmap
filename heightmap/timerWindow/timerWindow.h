#pragma once

class TimerWindow final : public core::Form, public core::Getter<TimerWindow> {
public:
	core::Slider daySlider;
	core::Slider yearSlider;
	core::Label dayLabel;
	core::Label yearLabel;

	void onOpening() override;
	void onOpened() override;
	void onClosing() override;

	void onEndPaint(const core::eventInfo& e) override;
	int onResize(const core::eventInfo& e) override;
};
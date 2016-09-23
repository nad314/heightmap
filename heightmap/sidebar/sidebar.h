#pragma once

class Sidebar final : public core::Frame {
public:
	core::Image difImage;
	core::Image norImage;
	core::Image relImage;

	core::ImageButton difButton; //diffuse texture load
	core::ImageButton norButton; //normal texture load
	core::ImageButton relButton; //reload textures
	core::Button clearButton;
	core::Slider sizeSlider;
	core::Button saveButton;
	core::Button loadButton;

	char difPath[256];
	char norPath[256];

	void onOpening() override;
	void onOpened() override;
	void loadImages();
	void adjustImage(core::Image& source, const core::Image& dest);
	void loadDifImage(const char* path);
	void loadNorImage(const char* path);

	void onEndPaint(const core::eventInfo& e) override;
};

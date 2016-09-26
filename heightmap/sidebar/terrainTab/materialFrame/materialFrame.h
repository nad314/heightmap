#pragma once

class MaterialFrame final: public core::Frame {
public:
	core::buffer<core::ImageButton*> button;

	void onOpening() override;
	void onOpened() override;
	void onClosed() override;
	void onEndPaint(const core::eventInfo& e) override;	
	void makeButtons();

	class MaterialButton final: public core::ImageButton, public core::Getter<MaterialButton> {
	public:
		core::glTextureMaterial* mat;
		MaterialButton& make(const core::vec4i& r, Form& f, core::glTextureMaterial *m, core::buttonFunc func);
	};
};

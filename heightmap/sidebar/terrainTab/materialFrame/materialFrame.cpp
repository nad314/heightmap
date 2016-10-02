#include <main/main.h>

void MaterialFrame::onOpening() {
	Frame::onOpening();
	setStyle(WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
	setFlags(0);
}

void MaterialFrame::onOpened() {
	Frame::onOpened();
	const int bsize = 52;
	setControlColors();
}

void MaterialFrame::onClosed() {
	Frame::onClosed();
	for (auto& i : button)
		delete i;
	button.clear();
}

void MaterialFrame::onEndPaint(const core::eventInfo& e) {
	Frame::onEndPaint(e);
	//core::Core2D::drawRect(getClientRect(), core::Theme::controlBorderColor, *this);
}

void MaterialFrame::makeButtons() {
	Storage& data = Controller::get().storage();
	int c(0);
	const int margin = 4;
	const int bsize = 56;
	for (auto& i : data.textures) {
		MaterialButton* ib = new MaterialButton;
		vec4i rect = vec4i(c%4, c/4, c%4+1, c/4+1);
		rect *= vec4i(bsize-margin);
		rect += vec4i(margin, margin, 0, 0);
		push(ib->make(rect, *this, &i, [](core::Control& c, core::Form& f)->void {
			MaterialButton& This = dynamic_cast<MaterialButton&>(c);
			This.get().unpin();
			This.pin();
			This.set(This);
			Storage& data = Controller::get().storage();
			data.material = *This.mat;
			Controller::get().invalidate();
			//core::Debug::print("Using Material %d\n", This.mat - data.textures);
		}));
		button.push_back(ib);
		++c;
	}
	button[0]->pin();
	invalidate();
}

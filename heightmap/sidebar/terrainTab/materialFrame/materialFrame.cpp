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
	const int bsize = 52;
	for (auto& i : data.textures) {
		MaterialButton* ib = new MaterialButton;
		push(ib->make(core::Rect((c % 4)*(bsize+2) + 3, (c / 4)*(bsize + 2) + 2, (c % 4 + 1)*(bsize + 2)+1, ((c / 4) + 1)*(bsize + 2)), *this, &i, [](core::Control& c, core::Form& f)->void {
			MaterialButton& This = dynamic_cast<MaterialButton&>(c);
			This.get().unpin();
			This.pin();
			This.set(This);
			Storage& data = Controller::get().storage();
			data.material = *This.mat;
			Controller::get().invalidate();
			core::Debug::print("Using Material %d\n", This.mat - data.textures);

		}));
		button.push_back(ib);
		++c;
	}
	invalidate();
}

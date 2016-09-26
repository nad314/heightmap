#include <main/main.h>

void MaterialFrame::onOpening() {
	Frame::onOpening();
	setStyle(WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
	setFlags(0);
	setClass("sidebarMaterialFrame");
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
	core::Core2D::drawRect(getClientRect(), core::Theme::controlBorderColor, *this);
}

void MaterialFrame::makeButtons() {
	Storage& data = Controller::get().storage();
	int c(0);
	const int bsize = 52;
	for (auto& i : data.textures) {
		core::Image* img = new core::Image;
		i.diffuse.construct(*img);
		Sidebar::adjustImage(*img, *img, bsize);
		core::ImageButton* ib = new core::ImageButton;
		push(ib->make(core::Rect((c % 4)*(bsize+2) + 3, (c / 4)*(bsize + 2) + 2, (c % 4 + 1)*(bsize + 2)+1, ((c / 4) + 1)*(bsize + 2)), img, *this, [](core::Control& c, core::Form& f)->void {
			MaterialFrame& mf = dynamic_cast<MaterialFrame&>(f);
			if (!mf) return;
			int counter(0);
			for (auto& i : mf.button) {
				if (i == &c) {
					i->pin();
					Storage& data = Controller::get().storage();
					data.material = data.textures[counter];
					Controller::get().invalidate();
					core::Debug::print("Using Material %d\n", counter);
				}
				else if (i->pinned())i->unpin();
				++counter;
			}
		}));
		ib->prerender();
		delete img;
		button.push_back(ib);
		++c;
	}
	invalidate();
}

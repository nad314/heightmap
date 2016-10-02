#include <main/main.h>

void TerrainTab::onOpening() {
	Frame::onOpening();
	setSize(256, 256);
	setStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
}

void TerrainTab::onOpened() {
	Frame::onOpened();
	setBackColor(App::Theme::FormBackColor);

	const int sbw = App::Theme::sidebarClientWidth;
	core::Image img;
	img.make(18, 18, 32);
	vec4b clr = vec4b(64, 64, 68, 255);
	clr = core::Theme::backColor;
	//core::Core2D::fillRect(vec4i(3, 3, 16, 16), vec4b(64, 64, 68, 255), img);
	core::Core2D::fillRect(vec4i(0, 0, 18, 4), clr, img);
	core::Core2D::fillRect(vec4i(0, 14, 18, 18), clr, img);
	core::Core2D::fillRect(vec4i(0, 0, 4, 18), clr, img);
	core::Core2D::fillRect(vec4i(14, 0, 18, 18), clr, img);
	//core::Core2D::drawRect(vec4i(3, 3, 15, 15), core::Theme::controlBorderColor, img);
	core::Core2D::drawRect(vec4i(0, 0, 18, 18), /*core::Theme::controlBorderColor*/App::Theme::FormBackColor, img);
	//Sidebar::adjustImage(img, img, 18);
	
	/*
	push(matButton.make(vec4i(4, 4, 22, 22), &img, *this, [](core::Control& c, core::Form& f)->void {
		try {
			core::ImageButton& This = dynamic_cast<core::ImageButton&>(c);
			if (This.pinned())
				This.unpin();
			else This.pin();
		}
		catch (std::bad_cast& e) { core::Debug::error("%s\n", e.what()); }
	}));
	matButton.setBackColorHover(core::Theme::constrastBorderColor);
	matButton.prerender();
	*/

	push(matLabel.make(vec4i(26, 4, sbw, 22), "Draw Texture: ", *this).setAlign(0).setColor(core::Theme::constrastBorderColor));

	Rect next = nextVertical();
	matFrame.setParent(this);
	matFrame.open();
	push(&matFrame);
	matFrame.move(next + vec4i(4, 4, sbw-4, 164));

	next = nextVertical();
	push(brushLabel[0].make(next + vec4i(4, 4, 80, 24), "Size:", *this).setAlign(0).setColor(core::Theme::constrastBorderColor));
	push(brushSlider[0].make(next + vec4i(88, 4, sbw - 4, 24), 0, *this, [](float pos, core::Control& c, core::Form& f)->void {
		try {
			MaterialTool* tool = dynamic_cast<MaterialTool*>(Controller::get().getTool());
			tool->brush.metrics.x = pos;
			Controller::get().invalidate();
		}
		catch (std::bad_cast e) { core::Debug::log("%s\n", e.what()); }
	}));
	next = nextVertical();
	push(brushLabel[1].make(next + vec4i(4, 4, 80, 24), "Intensity:", *this).setAlign(0).setColor(core::Theme::constrastBorderColor));
	push(brushSlider[1].make(next + vec4i(88, 4, sbw - 4, 24), 0, *this, [](float pos, core::Control& c, core::Form& f)->void {
		try {
			MaterialTool* tool = dynamic_cast<MaterialTool*>(Controller::get().getTool());
			tool->brush.metrics.y = pos;
			Controller::get().invalidate();
		}
		catch (std::bad_cast e) { core::Debug::log("%s\n", e.what()); }
	}));
	next = nextVertical();
	push(brushLabel[2].make(next + vec4i(4, 4, 80, 24), "Step:", *this).setAlign(0).setColor(core::Theme::constrastBorderColor));
	push(brushSlider[2].make(next + vec4i(88, 4, sbw - 4, 24), 11, *this, [](float pos, core::Control& c, core::Form& f)->void {
		try {
			MaterialTool* tool = dynamic_cast<MaterialTool*>(Controller::get().getTool());
			tool->brush.step = pos;
			Controller::get().invalidate();
		}
		catch (std::bad_cast e) { core::Debug::log("%s\n", e.what()); }
	}));
	
	setControlColors();
}

int TerrainTab::onLButtonDown(const core::eventInfo& e) {
	if (Controller::get().busy)
		return e;
	return Frame::onLButtonDown(e);
}

int TerrainTab::onLButtonUp(const core::eventInfo& e) {
	if (Controller::get().busy)
		return e;
	return Frame::onLButtonUp(e);
}

void TerrainTab::load() {
	matFrame.makeButtons();
	adjustSliders();
}

void TerrainTab::adjustSliders() {
	try {
		MaterialTool* tool = dynamic_cast<MaterialTool*>(Controller::get().getTool());
		if (!tool) return;
		brushSlider[0].setPos(tool->brush.metrics.x);
		brushSlider[1].setPos(tool->brush.metrics.y);
		brushSlider[2].setPos(tool->brush.step);
	}
	catch (std::bad_cast e) { core::Debug::log("%s\n", e.what()); }
}

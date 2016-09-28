#include <main/main.h>


void Sidebar::adjustImage(core::Image& dest, const core::Image& source, const int& size) {
	core::Image img = source;
	const int border = 6;
	dest.make(size, size);
	img.linearDownscale(size -2* border, size -2* border);
	core::Core2D::clearImage(dest, core::Color(0,0,0,0));
	//core::Core2D::drawRect(core::Rect(0, 0, size, size), core::Theme::controlBorderColor, dest);
	core::Core2D::blendImage(core::Rect(border, border, size - border, size - border), img, dest);
}


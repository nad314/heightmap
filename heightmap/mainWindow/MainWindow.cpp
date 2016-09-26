#include <main/main.h>

void MainWindow::onOpening() {
	WindowForm::onOpening();
	setTitle("Core Terrain Editor");
	setClass("CoreMaterialPreview");
	setFlags(glw_hidden);
	setSize(1024, 720);
}

void MainWindow::onClosing() {
	statusbar.close();
	sidebar.close();
	renderWindow.close();
	WindowForm::onClosing();
}

void MainWindow::onOpened() {
	WindowForm::onOpened();
	renderWindow.setParent(this);
	renderWindow.open();
	sidebar.setParent(this);
	sidebar.open();
	statusbar.setParent(this);
	statusbar.open();
	reshape();
}

int MainWindow::onResize(const core::eventInfo& e) {
	WindowForm::onResize(e);
	if (width < 1 || height < 1)
		return e;
	reshape();
	return e;
}

int MainWindow::onGetMinMaxInfo(const core::eventInfo& e) {
	LPMINMAXINFO lpMMI = (LPMINMAXINFO)e.lP;
	lpMMI->ptMinTrackSize.x = 800;
	lpMMI->ptMinTrackSize.y = 600;
	return e;
}

void MainWindow::reshape() {
	renderWindow.move(vec4i(8, 40, width - 6 - App::Theme::sidebarWidth, height - 30));
	sidebar.move(vec4i(width - App::Theme::sidebarWidth, 40, width - 8, height - 30));
	statusbar.move(vec4i(3, height - 24, width - 3, height-4));
}

void MainWindow::onEndPaint(const core::eventInfo& e) {
	WindowForm::onEndPaint(e);
	core::Core2D::drawRect(renderWindow.getChildRect().expand(1), core::Color(10), *this);
	core::Core2D::drawRect(sidebar.getChildRect().expand(1), core::Color(10), *this);
	core::Core2D::drawRect(statusbar.getChildRect().expand(1), core::Color(10), *this);
	InvalidateRect(renderWindow, NULL, false);
}

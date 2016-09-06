#include <main/main.h>

void MainWindow::onOpening() {
	WindowForm::onOpening();
	setTitle("Core Heightmap Editor");
	setClass("CoreHeightmapEditor");
	setFlags(glw_hidden);
}

void MainWindow::onClosing() {
	renderWindow.close();
	WindowForm::onClosing();
}

void MainWindow::onOpened() {
	WindowForm::onOpened();
	renderWindow.setParent(this);
	renderWindow.open();
	reshape();
}

int MainWindow::onResize(const core::eventInfo& e) {
	WindowForm::onResize(e);
	if (width < 1 || height < 1)
		return e;
	reshape();
	return e;
}

void MainWindow::reshape() {
	MoveWindow(renderWindow.hWnd, 6, 40, width - 12, height - 46, false);
}

void MainWindow::onEndPaint(const core::eventInfo& e) {
	WindowForm::onEndPaint(e);
	core::Core2D::drawRect(renderWindow.getChildRect().expand(1), core::Color(10), *this);
}

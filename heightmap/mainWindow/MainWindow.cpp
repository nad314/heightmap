#include <main/main.h>

void MainWindow::onOpening() {
	WindowForm::onOpening();
	setTitle("Core Heightmap Editor");
	setClass("CoreHeightmapEditor");
	setStyle(WS_POPUP);
}

void MainWindow::onClosing() {
	renderWindow.close();
	WindowForm::onClosing();
}

void MainWindow::onOpened() {
	WindowForm::onOpened();
	GL::setVsync(0);
	renderWindow.setParent(this);
	renderWindow.open();
	reshape();
}

void MainWindow::onClosed() {
	WindowForm::onClosed();
}

int MainWindow::onResize(const core::eventInfo& e) {
	int ret = WindowForm::onResize(e);
	reshape();
	return ret;
}

void MainWindow::reshape() {
	MoveWindow(renderWindow.hWnd, 6, 40, width - 12, height - 46, true);
}

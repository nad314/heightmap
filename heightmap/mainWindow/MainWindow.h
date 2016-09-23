#pragma once
class MainWindow final : public core::WindowForm {
public:
	RenderWindow renderWindow;
	Sidebar sidebar;
	Statusbar statusbar;
public:
	void onOpening() override;
	void onClosing() override;
	void onOpened() override;

	int onResize(const core::eventInfo& e) override;
	int onGetMinMaxInfo(const core::eventInfo& e) override;
	void onEndPaint(const core::eventInfo& e) override;
	void reshape();

};

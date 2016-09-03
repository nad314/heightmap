#pragma once
class MainWindow final : public core::WindowForm {
public:
	RenderWindow renderWindow;
public:
	void onOpening() override;
	void onClosing() override;
	void onOpened() override;

	int onResize(const core::eventInfo& e) override;
	void onEndPaint(const core::eventInfo& e) override;
	void reshape();
};

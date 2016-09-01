#pragma once
class MainWindow final : public core::WindowForm {
public:
	RenderWindow renderWindow;
public:
	void onOpening() override;
	void onClosing() override;
	void onOpened() override;
	void onClosed() override;

	int onPaint(const core::eventInfo& e) override;
	int onResize(const core::eventInfo& e) override;

	void reshape();
};

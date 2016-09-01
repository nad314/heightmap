#pragma once

class Program final : public core::Module, public core::SIMD {
protected:
	MainWindow wnd; //view
	Controller* controller; //controller
	Storage* data; //model

public:
	int onLoad() override;
	int onDispose() override;

	int onStart() override;
	int onStop() override;
	int main() override;
};

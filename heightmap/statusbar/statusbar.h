#pragma once

class Statusbar final : public core::Form, public core::Debugger {
protected:
	static Statusbar* currentStatusbar;
	FILE* output;
	char text[256];
	std::mutex iomutex;
public:
	core::ProgBar progBar;
	Statusbar() :Form(), Debugger() { 
		core::Debug::attach(this); 
		currentStatusbar = this; 
		core::Path::pushDir();
		core::Path::goHome();
		core::Path::cd("../data/");
		output = fopen((core::Path::getDir() + "\\log.txt").c_str(), "w");
		core::Path::popDir();
	}
	~Statusbar() { fclose(output); }
	void onOpening() override;
	void onOpened() override;

	void onStartPaint(const core::eventInfo& e) override;
	void onEndPaint(const core::eventInfo& e) override;
	int onResize(const core::eventInfo& e) override;
	void print(const char* s) override;
	void log(const char* s) override;
	void info(const char* s) override;
	void error(const char* s) override;

	static inline Statusbar& get() { return *currentStatusbar; }
	static inline void prog(float amount) { get().progBar.set(amount); }
};

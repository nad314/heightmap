#pragma once

class Controller : public core::EventListener {
protected:
	core::Window* parent;
	Storage* data;
	static bool repaint;
public:
	Controller() : EventListener(), parent(NULL) {}
	Controller(core::Window* prt, Storage* storage);
	~Controller();

	int onPaint(const core::eventInfo& e) override;

	void drawScene();
	static inline void invalidate() { repaint = 1; }
};

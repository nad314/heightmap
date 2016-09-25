#pragma once

class Controller : public core::EventListener {
protected:
	static Controller* defController;
	core::Window* parent;
	Storage* lpdata;
	static bool repaint;
	core::vec2i mpos;
	bool dragging;
	bool isbusy = 0;

	core::matrixf rotation, translation;

public:
	static bool busy;
	Controller() : EventListener(), parent(NULL) { defController = this; }
	Controller(core::Window* prt, Storage* storage);
	~Controller();

	int onPaint(const core::eventInfo& e) override;
	int onResize(const core::eventInfo& e) override;
	int onLButtonDown(const core::eventInfo& e) override;
	int onLButtonUp(const core::eventInfo& e) override;
	int onMouseMove(const core::eventInfo& e) override;

	void drawScene();
	void initGL();
	static inline void invalidate() { repaint = 1; }
	inline static Controller& get() { return *defController; }
	inline Storage& storage() { return *lpdata; }

	void clearTextures();
	void makeImage(core::glTexture& texture, core::Image& image);
	inline core::Window* getParent() { return parent; }
};

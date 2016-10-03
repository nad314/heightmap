#pragma once

class Controller final : public core::EventListener, public core::Getter<Controller> {
protected:
	core::Window* parent;
	Storage* lpdata;
	static bool repaint;
	core::vec2i mpos;
	bool dragging;
	bool isbusy = 0;
	core::EventListener* tool = NULL;

	core::matrixf rotation, translation, pan;

public:
	static bool busy;
	Controller() : EventListener(), parent(NULL) { set(*this); }
	Controller(core::Window* prt, Storage* storage);
	~Controller();

	int onPaint(const core::eventInfo& e) override;
	int onResize(const core::eventInfo& e) override;
	int onLButtonDown(const core::eventInfo& e) override;
	int onLButtonUp(const core::eventInfo& e) override;
	int onRButtonDown(const core::eventInfo& e) override;
	int onRButtonUp(const core::eventInfo& e) override;
	int onMouseMove(const core::eventInfo& e) override;

	void drawScene(const core::eventInfo& e);
	void initGL();
	static inline void invalidate() { repaint = 1; }
	inline Storage& storage() { return *lpdata; }

	void clearTextures();
	void makeImage(core::glTexture& texture, core::Image& image);
	inline core::Window* getParent() { return parent; }
	inline core::EventListener* getTool() { return tool; }

	static void lock();
	static void unlock();

	//transform
	void initViewMatrix();
	void updateViewMatrix();
	bool raytrace(vec3& point, const vec2i& mp);
};

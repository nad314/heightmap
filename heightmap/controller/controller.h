#pragma once

class Controller : public core::EventListener {
protected:
	core::Window* parent;
	Storage* data;
public:
	Controller() : EventListener(), parent(NULL) {}
	Controller(core::Window* prt, Storage* storage);
	~Controller();
};

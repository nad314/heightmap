#pragma once

class Controller : public core::EventListener {
protected:
	core::Window* parent;
public:
	Controller(): EventListener(), parent(NULL){}
	Controller(core::Window* prt):parent(prt) {}
};

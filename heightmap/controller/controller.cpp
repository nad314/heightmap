#include <main\main.h>

Controller::Controller(core::Window* ptr, Storage* storage) {
	parent = ptr;
	parent->attach(this);
	data = storage;
}

Controller::~Controller() {
	if (parent)
		parent->detach();
	data = NULL;
}

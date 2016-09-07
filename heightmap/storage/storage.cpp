#include <main/main.h>

Storage::Storage() {
	core::Path::pushDir();
	core::Path::goHome();
	core::Path::cd("../data/");
	img.loadPng("core.png");
	core::Path::popDir();
}

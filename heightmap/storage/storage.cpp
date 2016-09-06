#include <main/main.h>

Storage::Storage() {
	core::Path::pushDir();
	core::Path::goHome();
	core::Path::cd("../data/");
	img.loadPng("dragon2.png");
	core::Path::popDir();
}

#include <main/main.h>

Storage::Storage() {
	core::Path::pushDir();
	core::Path::goHome();
	img.loadPng("data/dragon2.png");
	img.savePng("data/saved.png");
	core::Path::popDir();
}
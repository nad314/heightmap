#include <main/main.h>

Storage::Storage() {
	core::Path::pushDir();
	core::Path::goHome();
	img.loadTga("data/dragon.tga");
	core::Path::popDir();
}
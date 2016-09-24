#include <main/main.h>

Storage::Storage() {
	core::Path::pushDir();
	core::Path::goHome();
	core::Path::cd("../data/");
	Cube cube;
	if (!shader.load("shaders/default/vertex.glsl", "shaders/default/fragment.glsl", "fragColor"))
		core::Debug::print("Could not load shaders\n");
	else shader.printDebugInfo();
	model.make(cube, shader, "pos", "nor", "tan", "btan", "tex");
	core::Path::popDir();
	loadTextureMaterials();
}

Storage::~Storage() {
	for (auto& i : textures)
		i.dispose();
}

void Storage::loadTextureMaterials() {
	std::string cdir = core::Path::getDir()+"\\";
	core::Path::goHome();
	core::Path::cd("../");
	core::buffer<std::string> files;
	std::string path = core::Path::getDir() + "\\data\\materials\\";
	files = core::Path::listFiles((path+"*.mat").c_str());
	textures.clear();
	textures.reserve(files.count());
	for (auto& i : files) {
		core::Debug::print("Loading '%s'...", i.c_str());
		core::glTextureMaterial* mat = new core::glTextureMaterial;
		if (mat->load((path+i).c_str(), core::Path::getHomeDir().c_str())) {
			mat->genMipmaps();
			textures.push_back(*mat);
			core::Debug::print("OK\n");
		}
		else {
			core::Debug::print("FAIL\n");
			delete mat;
		}
	}
	core::Path::cd(cdir.c_str());
}

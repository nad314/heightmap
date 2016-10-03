#include <main/main.h>

Storage::Storage() {
	core::Path::pushDir();
	core::Path::goHome();
	core::Path::cd("../data/");
	Cube cube;
	if (!shader.load("shaders/default/vertex.glsl", "shaders/default/fragment.glsl", "fragColor"))
		core::Debug::error("Could not load shaders\n");
	else shader.printDebugInfo();
	model.make(cube, shader, "pos", "nor", "tan", "btan", "tex");
	core::Path::popDir();
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
	Statusbar::prog(0);
	int c = 0;
	for (auto& i : files) {
		core::Debug::print("Loading '%s'...", i.c_str());
		core::glTextureMaterial* mat = new core::glTextureMaterial;
		if (mat->load((path+i).c_str(), core::Path::getHomeDir().c_str())) {
			mat->genMipmaps();
			textures.push_back(*mat);
			core::Debug::log("OK\n");
		}
		else {
			core::Debug::log("FAIL\n");
			delete mat;
		}
		++c;
		Statusbar::prog((float)c / files.count());
	}
	core::Path::cd(cdir.c_str());
	Statusbar::prog(0);
	core::Debug::print("Loaded Materials.\n");
}

void Storage::load() {
	loadTextureMaterials();
	if (textures.count())
		material = textures[0];
	chunk.buildSimple(vec4(-1, 1, 1, -1), shader);
	map.buildSimple(8, 8, shader);
}


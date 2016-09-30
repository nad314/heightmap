#include <main/main.h>

Storage::Storage() {
	core::Path::pushDir();
	core::Path::goHome();
	core::Path::cd("../data/");
	Cube cube;
	if (!shader.load("shaders/default/vertex.glsl", "shaders/default/fragment.glsl", "fragColor"))
		core::Debug::error("Could not load shaders\n");
	else shader.printDebugInfo();
	if (!compute.load("shaders/compute/drawTexture.glsl"))
		core::Debug::error("Could not load compute shader\n");
	else compute.printDebugInfo();
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

	vec2 imageSize = vec2(512);
	vec2 pos = vec2(0.0f);
	vec4 rect = vec4(-1, 1, 1, -1);
	vec2 chunkPos = vec2(0.0f);
	compute.start();
	glExt::uniform2fv(glExt::getUniformLocation(compute, "cursor"), 1, pos);
	glExt::uniform4fv(glExt::getUniformLocation(compute, "rect"), 1, rect);
	glExt::uniform2fv(glExt::getUniformLocation(compute, "texSize"), 1, imageSize);
	glExt::uniform2fv(glExt::getUniformLocation(compute, "texScale"), 1, material.scale);
	glExt::uniform2fv(glExt::getUniformLocation(compute, "chunkPos"), 1, chunkPos);

	glExt::uniform1i(glExt::getUniformLocation(compute, "matDiffuse"), 0);
	glExt::uniform1i(glExt::getUniformLocation(compute, "matNormal"), 1);
	material.diffuse.bind(0);
	material.normal.bind(1);

	glExt::bindImageTexture(1, chunk.material.diffuse, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA8);
	glExt::bindImageTexture(2, chunk.material.normal, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA8);
	glExt::dispatchCompute((int)imageSize.x / 16, (int)imageSize.y / 16, 1);
	compute.stop();
}

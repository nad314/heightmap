#include <main/main.h>

Storage::Storage() {
	core::Path::pushDir();
	core::Path::goHome();
	core::Path::cd("../data/");
	Cube cube;
	if (!shader.load("vertex.glsl", "fragment.glsl", "fragColor"))
		core::Debug::print("Could not load shaders\n");
	else shader.printDebugInfo();
	model.make(cube, shader, "pos", "nor", "tan", "btan", "tex");
	core::Path::popDir();
}

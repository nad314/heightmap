#include <main/main.h>

MaterialTool* core::Getter<MaterialTool>::getter = NULL;

MaterialTool::MaterialTool() {
	core::Path::pushDir();
	core::Path::goHome();
	core::Path::cd("../data/");
	if (!compute.load("shaders/compute/drawTexture.glsl"))
		core::Debug::error("Could not load compute shader\n");
	else compute.printDebugInfo();
	core::Path::popDir();

	compute.start();
	uniform[0] = glExt::getUniformLocation(compute, "cursor");
	uniform[7] = glExt::getUniformLocation(compute, "brush");
	uniform[1] = glExt::getUniformLocation(compute, "rect");
	uniform[2] = glExt::getUniformLocation(compute, "texSize");
	uniform[4] = glExt::getUniformLocation(compute, "chunkPos");

	uniform[5] = glExt::getUniformLocation(compute, "matDiffuse");
	uniform[6] = glExt::getUniformLocation(compute, "matNormal");
	uniform[3] = glExt::getUniformLocation(compute, "matScale");
	compute.stop();
}

MaterialTool::~MaterialTool() {}

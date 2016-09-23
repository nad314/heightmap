#pragma once

struct Storage: public core::SIMD {
public:
	core::glView view;
	core::glGameMesh model;
	core::glShader shader;
	core::glTextureMaterial material;
	Storage();
};

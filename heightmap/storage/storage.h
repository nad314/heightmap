#pragma once

struct Storage: public core::SIMD {
public:
	core::glView view;
	core::glGameMesh model;
	core::glShader shader;
	core::glTextureMaterial material;
	core::buffer<core::glTextureMaterial> textures;

	craft::ChunkMesh chunk;
	Storage();
	~Storage();

	void loadTextureMaterials();
	void load();
};

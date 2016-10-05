#pragma once

struct Storage: public core::SIMD {
public:
	core::glView view;
	core::Frustum frustum;
	core::glGameMesh model;
	core::glShader shader;
	core::glTextureMaterial material;
	core::buffer<core::glTextureMaterial> textures;

	craft::ChunkMesh chunk;
	craft::Map map;
	Storage();
	~Storage();

	void loadTextureMaterials();
	void load();
};

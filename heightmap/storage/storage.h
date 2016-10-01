#pragma once

struct Storage: public core::SIMD {
public:
	core::glView view;
	core::glGameMesh model;
	core::glShader shader;
	core::glTextureMaterial material;
	core::buffer<core::glTextureMaterial> textures;

	craft::ChunkMesh chunk;
	core::glComputeShader compute;
	Storage();
	~Storage();

	void loadTextureMaterials();
	void load();
	void sendCompute(const vec3& pos);
};

#pragma once

namespace craft {
	struct Field {
		byte level;
	};

	struct Chunk {
		static const int chunkSize = 16;
		Field data[chunkSize*chunkSize];

		inline Field& at(const int &x, const int& y) { return data[y*chunkSize + x]; }
	};

	struct ChunkMesh: public core::SIMD {
		vec4 rect;
		vec4 texRect;
		vec2 pos;
		core::glGameMesh mesh;
		core::glTextureMaterial material;

		inline void draw() { mesh.drawTris(); }
		ChunkMesh& buildSimple(const vec4& r, core::glShader& shader);
		ChunkMesh& buildSimple(const int& x, const int& y, core::glShader& shader);
	};
}

#pragma once

namespace craft {
	class Map {
	public:
		vec2i size; // x*y in chunks
		core::buffer<Chunk> chunk;
		core::buffer<ChunkMesh> mesh;

		Map& dispose();
		Map& buildSimple(const int& x, const int& y, core::glShader& shader);
	};
}

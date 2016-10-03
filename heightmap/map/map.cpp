#include <main/main.h>

namespace craft {
	Map& Map::dispose() {
		size = vec2i(0);
		chunk.clear();
		mesh.clear();
		return *this;
	}

	Map& Map::buildSimple(const int& x, const int& y, core::glShader& shader) {
		dispose();
		size = vec2i(x, y);
		chunk.reserve(x*y);
		chunk.count() = x*y;
		mesh.reserve(x*y);
		mesh.count() = x*y;
		for (int i = 0; i < y; ++i)
			for (int j = 0; j < x; ++j)
				mesh[i*x + j].buildSimple(j, i, shader);
		return *this;
	}

}

#include <main/main.h>

namespace craft {
	ChunkMesh& ChunkMesh::buildSimple(const vec4& r, core::glShader& shader) {
		rect = r;
		texRect = vec4(0, 0, 1, 1);
		core::GameMesh m;
		m.position.push_back(vec3(r.x, 0, r.y));
		m.position.push_back(vec3(r.z, 0, r.y));
		m.position.push_back(vec3(r.z, 0, r.w));
		m.position.push_back(vec3(r.x, 0, r.w));

		m.texcoord.push_back(vec2(0, 0));
		m.texcoord.push_back(vec2(1, 0));
		m.texcoord.push_back(vec2(1, 1));
		m.texcoord.push_back(vec2(0, 1));

		m.indices.push_back(0);
		m.indices.push_back(1);
		m.indices.push_back(2);
		m.indices.push_back(0);
		m.indices.push_back(2);
		m.indices.push_back(3);

		m.computeNormals();

		mesh.make(m, shader, "pos", "nor", "tan", "btan", "tex");
		material.makeDefault(512);
		material.diffuse.bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		material.normal.bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		material.normal.unbind();
		return *this;
	}
}

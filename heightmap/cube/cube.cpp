#include <main/main.h>

void Cube::make(const float& r) {
	position.push_back(core::vec3(r, -r, -r));
	position.push_back(core::vec3(-r, -r, -r));
	position.push_back(core::vec3(-r, r, -r));
	position.push_back(core::vec3(r, r, -r));

	position.push_back(core::vec3(-r, -r, r));
	position.push_back(core::vec3(r, -r, r));
	position.push_back(core::vec3(r, r, r));
	position.push_back(core::vec3(-r, r, r));

	position.push_back(core::vec3(-r, -r, -r));
	position.push_back(core::vec3(-r, -r, r));
	position.push_back(core::vec3(-r, r, r));
	position.push_back(core::vec3(-r, r, -r));

	position.push_back(core::vec3(r, -r, -r));
	position.push_back(core::vec3(r, r, -r));
	position.push_back(core::vec3(r, r, r));
	position.push_back(core::vec3(r, -r, r));

	position.push_back(core::vec3(-r, -r, -r));
	position.push_back(core::vec3(r, -r, -r));
	position.push_back(core::vec3(r, -r, r));
	position.push_back(core::vec3(-r, -r, r));

	position.push_back(core::vec3(r, r, -r));
	position.push_back(core::vec3(-r, r, -r));
	position.push_back(core::vec3(-r, r, r));
	position.push_back(core::vec3(r, r, r));

	for (int i = 0; i < 6; ++i) {
		texcoord.push_back(core::vec2(0, 0));
		texcoord.push_back(core::vec2(1, 0));
		texcoord.push_back(core::vec2(1, 1));
		texcoord.push_back(core::vec2(0, 1));
	}

	for (int i = 0; i < 24; i += 4) {
		indices.push_back(i);
		indices.push_back(i+1);
		indices.push_back(i+2);
		indices.push_back(i);
		indices.push_back(i+2);
		indices.push_back(i+3);
	}

	computeNormals();
}
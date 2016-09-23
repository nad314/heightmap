#pragma once

class Cube : public core::GameMesh {
public:
	Cube() { make(1.0); }
	Cube(const float& f) { make(f); }
	void make(const float& r);
};
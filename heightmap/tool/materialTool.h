#pragma once

class MaterialTool final : public core::EventListener, public core::Getter<MaterialTool> {
private:
	core::glComputeShader compute;
	core::glShader brushDisplay;
	uint uniform[8];
	uint brushUniform[4];
	uint brushAttrib[2];

	vec2i mpos;
	vec2i lpos;
	vec3 lastPoint;
	vec3 position;

	bool drawing = 0;
	bool traced = 0;
public:

	struct Brush {
		vec2 metrics; //(radius, intensity)
		float step; //percent of radius needed to travel to draw
		Brush() : metrics(0.5f, 0.5f), step(0.2f) {}
	} brush;

	MaterialTool();
	~MaterialTool();

	int onPaint(const core::eventInfo& e) override;
	int onLButtonDown(const core::eventInfo& e) override;
	int onLButtonUp(const core::eventInfo& e) override;
	int onMouseMove(const core::eventInfo& e) override;

	bool raytrace(vec3& point);
	MaterialTool& sendCompute(const vec3& point);
	MaterialTool& drawBrush(const vec3& point);
};


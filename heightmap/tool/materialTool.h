#pragma once

class MaterialTool final : public core::EventListener, public core::Getter<MaterialTool> {
private:
	core::glComputeShader compute;
	uint uniform[8];
	vec2i mpos;
	vec2i lpos;
	vec3 lastPoint;
	bool drawing = 0;
public:

	struct Brush {
		vec2 metrics; //(radius, intensity)
		Brush() : metrics(1.0f, 0.5f) {}
	} brush;

	MaterialTool();
	~MaterialTool();

	int onPaint(const core::eventInfo& e) override;
	int onLButtonDown(const core::eventInfo& e) override;
	int onLButtonUp(const core::eventInfo& e) override;
	int onMouseMove(const core::eventInfo& e) override;

	bool raytrace(vec3& point);
	MaterialTool& sendCompute(const vec3& point);
};

